// Copyright 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import BraveCore
import BraveShields
import Preferences
@_spi(ChromiumWebViewAccess) import Web
import os.log

extension TabDataValues {
  private struct CosmeticFilteringTabHelperKey: TabDataKey {
    static var defaultValue: CosmeticFilteringTabHelper?
  }
  public var cosmeticFilteringTabHelper: CosmeticFilteringTabHelper? {
    get { self[CosmeticFilteringTabHelperKey.self] }
    set { self[CosmeticFilteringTabHelperKey.self] = newValue }
  }
}

public class CosmeticFilteringTabHelper: TabObserver {

  private weak var tab: (any TabState)?
  private var cosmeticFilteringArgs: [String: CosmeticFilteringArgs] = .init()

  public init(
    tab: some TabState
  ) {
    self.tab = tab
    tab.addObserver(self)
  }

  // MARK: - TabObserver

  public func tabDidCreateWebView(_ tab: some TabState) {
    BraveWebView.from(tab: tab)?.setCosmeticFilteringTabHelperBridge(self)
  }

  public func tabWillBeDestroyed(_ tab: some TabState) {
    tab.removeObserver(self)
  }

  /// Combine new selectors with the cached selectors for the tab's visibleURL.
  private func standardAndAggressiveSelectors(
    from models: [AdBlockGroupsManager.CosmeticFilterModelTuple]
  ) -> (Set<String>, Set<String>) {
    var cachedStandardSelectors: Set<String> = .init()
    var cachedAggressiveSelectors: Set<String> = .init()
    if let url = tab?.visibleURL,
      let (standard, aggressive) = tab?.contentBlocker?.cachedSelectors(for: url)
    {
      cachedStandardSelectors = standard
      cachedAggressiveSelectors = aggressive
    }
    var standardSelectors: Set<String> = cachedStandardSelectors
    var aggressiveSelectors: Set<String> = cachedAggressiveSelectors
    for modelTuple in models {
      if modelTuple.isAlwaysAggressive {
        aggressiveSelectors = aggressiveSelectors.union(modelTuple.model.hideSelectors)
      } else {
        standardSelectors = standardSelectors.union(modelTuple.model.hideSelectors)
      }
    }
    return (standardSelectors, aggressiveSelectors)
  }
}

@MainActor extension CosmeticFilteringTabHelper: @MainActor CosmeticFilteringTabHelperBridge {

  public func cosmeticFilteringArgs(for url: URL) async -> CosmeticFilteringArgs {
    guard let tab = tab,
      let visibleURL = tab.visibleURL,
      let braveShieldsHelper = tab.braveShieldsHelper,
      // shield level is determined by the main frame
      case let mainFrameShieldLevel = braveShieldsHelper.shieldLevel(
        for: visibleURL,
        considerAllShieldsOption: true
      ),
      mainFrameShieldLevel.isEnabled,
      visibleURL.isWebPage(includeDataURIs: false)
    else {
      return .empty
    }

    let models = await AdBlockGroupsManager.shared.cosmeticFilterModels(
      forFrameURL: url,
      isAdBlockEnabled: mainFrameShieldLevel.isEnabled
    )
    let (standardSelectors, aggressiveSelectors) = standardAndAggressiveSelectors(from: models)

    var proceduralActions: Set<String> = []
    for modelTuple in models {
      proceduralActions = proceduralActions.union(modelTuple.model.proceduralActions)
    }

    return CosmeticFilteringArgs(
      hideFirstPartyContent: mainFrameShieldLevel.isAggressive,
      genericHide: models.contains { $0.model.genericHide },
      firstSelectorsPollingDelayMs: nil,
      switchToSelectorsPollingThreshold: NSNumber(integerLiteral: 1000),
      fetchNewClassIdRulesThrottlingMs: NSNumber(integerLiteral: 100),
      aggressiveSelectors: aggressiveSelectors,
      standardSelectors: standardSelectors,
      proceduralFilters: proceduralActions
    )
  }

  public func selectorsToHide(
    for frameURL: URL,
    ids: Set<String>,
    classes: Set<String>,
  ) async -> (Set<String>, Set<String>) {
    guard let tabPageData = tab?.currentPageData else {
      return (.init(), .init())
    }
    let cachedEngines = AdBlockGroupsManager.shared.cachedEngines(
      isAdBlockEnabled: tab?.braveShieldsHelper?.shieldLevel(
        for: tabPageData.mainFrameURL,
        considerAllShieldsOption: true
      ).isEnabled ?? true
    )

    let selectorArrays = await cachedEngines.asyncCompactMap {
      cachedEngine -> (selectors: Set<String>, isAlwaysAggressive: Bool)? in
      do {
        guard
          let selectors = try await cachedEngine.selectorsForCosmeticRules(
            frameURL: frameURL,
            ids: Array(ids),
            classes: Array(classes)
          )
        else {
          return nil
        }

        return await (selectors, cachedEngine.type.isAlwaysAggressive)
      } catch {
        Logger.module.error("\(error.localizedDescription)")
        return nil
      }
    }

    var standardSelectors: Set<String> = []
    var aggressiveSelectors: Set<String> = []
    for tuple in selectorArrays {
      if tuple.isAlwaysAggressive {
        aggressiveSelectors = aggressiveSelectors.union(tuple.selectors)
      } else {
        standardSelectors = standardSelectors.union(tuple.selectors)
      }
    }

    // cache blocked selectors
    if let url = tab?.visibleURL {
      tab?.contentBlocker?.cacheSelectors(
        for: url,
        standardSelectors: standardSelectors,
        aggressiveSelectors: aggressiveSelectors
      )
    }
    return (standardSelectors, aggressiveSelectors)
  }
}

extension CosmeticFilteringArgs {
  fileprivate static let empty: CosmeticFilteringArgs = .init(
    hideFirstPartyContent: false,
    genericHide: false,
    firstSelectorsPollingDelayMs: nil,
    switchToSelectorsPollingThreshold: NSNumber(integerLiteral: 1000),
    fetchNewClassIdRulesThrottlingMs: NSNumber(integerLiteral: 100),
    aggressiveSelectors: .init(),
    standardSelectors: .init(),
    proceduralFilters: .init()
  )
}
