/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_SEARCH_ENGINES_BRAVE_PREPOPULATED_ENGINES_H_
#define BRAVE_COMPONENTS_SEARCH_ENGINES_BRAVE_PREPOPULATED_ENGINES_H_

#include "base/containers/fixed_flat_map.h"
#include "build/build_config.h"
#include "third_party/search_engines_data/resources/definitions/prepopulated_engines.h"

namespace TemplateURLPrepopulateData {

// ****************************************************************************
// IMPORTANT! Bumped para 33 — adicionado PREPOPULATED_ENGINE_ID_SEARXGO
// e searxgo engine. Bump obrigatório a cada mudança de engines.
// ****************************************************************************

inline constexpr int kBraveCurrentDataVersion = 33;  // era 32, bumped +1

// DO NOT CHANGE THIS ONE. Used for backfilling kBraveDefaultSearchVersion.
inline constexpr int kBraveFirstTrackedDataVersion = 6;

// LINT.IfChange
enum BravePrepopulatedEngineID : unsigned int {
  PREPOPULATED_ENGINE_ID_INVALID = 0,

  // IDs já definidos no prepopulated_engines.json do Chromium
  PREPOPULATED_ENGINE_ID_GOOGLE = 1,
  PREPOPULATED_ENGINE_ID_YAHOO_JP = 2,
  PREPOPULATED_ENGINE_ID_BING = 3,
  PREPOPULATED_ENGINE_ID_YANDEX = 15,
  PREPOPULATED_ENGINE_ID_NAVER = 67,
  PREPOPULATED_ENGINE_ID_DAUM = 68,
  PREPOPULATED_ENGINE_ID_ECOSIA = 101,

  // IDs Brave — não definidos no Chromium
  BRAVE_PREPOPULATED_ENGINES_START = 500,
  PREPOPULATED_ENGINE_ID_AMAZON = 500,
  PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
#if BUILDFLAG(IS_ANDROID)
  PREPOPULATED_ENGINE_ID_DUCKDUCKGO_LITE,
#endif
  PREPOPULATED_ENGINE_ID_FINDX,
  PREPOPULATED_ENGINE_ID_GITHUB,
  PREPOPULATED_ENGINE_ID_INFOGALACTIC,
  PREPOPULATED_ENGINE_ID_MDNWEBDOCS,
  PREPOPULATED_ENGINE_ID_QWANT,
  PREPOPULATED_ENGINE_ID_SEARX,
  PREPOPULATED_ENGINE_ID_SEMANTICSCHOLAR,
  PREPOPULATED_ENGINE_ID_STACKOVERFLOW,
  PREPOPULATED_ENGINE_ID_STARTPAGE,
  PREPOPULATED_ENGINE_ID_TWITTER,
  PREPOPULATED_ENGINE_ID_WIKIPEDIA,
  PREPOPULATED_ENGINE_ID_WOLFRAMALPHA,
  PREPOPULATED_ENGINE_ID_YOUTUBE,
  PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE,
  PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE,

  // Yahoo deprecated (12/2020)
  PREPOPULATED_ENGINE_ID_YAHOO,
  PREPOPULATED_ENGINE_ID_YAHOO_AR,
  PREPOPULATED_ENGINE_ID_YAHOO_AT,
  PREPOPULATED_ENGINE_ID_YAHOO_AU,
  PREPOPULATED_ENGINE_ID_YAHOO_BR,
  PREPOPULATED_ENGINE_ID_YAHOO_CA,
  PREPOPULATED_ENGINE_ID_YAHOO_CH,
  PREPOPULATED_ENGINE_ID_YAHOO_CL,
  PREPOPULATED_ENGINE_ID_YAHOO_CO,
  PREPOPULATED_ENGINE_ID_YAHOO_DE,
  PREPOPULATED_ENGINE_ID_YAHOO_DK,
  PREPOPULATED_ENGINE_ID_YAHOO_ES,
  PREPOPULATED_ENGINE_ID_YAHOO_FI,
  PREPOPULATED_ENGINE_ID_YAHOO_FR,
  PREPOPULATED_ENGINE_ID_YAHOO_HK,
  PREPOPULATED_ENGINE_ID_YAHOO_ID,
  PREPOPULATED_ENGINE_ID_YAHOO_IE,
  PREPOPULATED_ENGINE_ID_YAHOO_IN,
  PREPOPULATED_ENGINE_ID_YAHOO_IT,
  PREPOPULATED_ENGINE_ID_YAHOO_MX,
  PREPOPULATED_ENGINE_ID_YAHOO_MY,
  PREPOPULATED_ENGINE_ID_YAHOO_NL,
  PREPOPULATED_ENGINE_ID_YAHOO_NO,
  PREPOPULATED_ENGINE_ID_YAHOO_NZ,
  PREPOPULATED_ENGINE_ID_YAHOO_PE,
  PREPOPULATED_ENGINE_ID_YAHOO_PH,
  PREPOPULATED_ENGINE_ID_YAHOO_SE,
  PREPOPULATED_ENGINE_ID_YAHOO_SG,
  PREPOPULATED_ENGINE_ID_YAHOO_TH,
  PREPOPULATED_ENGINE_ID_YAHOO_TW,
  PREPOPULATED_ENGINE_ID_YAHOO_UK,
  PREPOPULATED_ENGINE_ID_YAHOO_VE,
  PREPOPULATED_ENGINE_ID_YAHOO_VN,

  PREPOPULATED_ENGINE_ID_BRAVE,
  PREPOPULATED_ENGINE_ID_BRAVE_TOR,

  // SearxGo — motor privado via instância SearXNG própria
  PREPOPULATED_ENGINE_ID_SEARXGO,
};
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

extern const PrepopulatedEngine searxgo;
extern const PrepopulatedEngine duckduckgo;
extern const PrepopulatedEngine duckduckgo_de;
extern const PrepopulatedEngine duckduckgo_au_nz_ie;
#if BUILDFLAG(IS_ANDROID)
extern const PrepopulatedEngine duckduckgo_lite;
#endif
extern const PrepopulatedEngine brave_ecosia;
extern const PrepopulatedEngine qwant;
extern const PrepopulatedEngine brave_startpage;
extern const PrepopulatedEngine brave_yandex;
extern const PrepopulatedEngine brave_search;
extern const PrepopulatedEngine brave_search_tor;
extern const PrepopulatedEngine brave_bing;
extern const PrepopulatedEngine brave_yahoo_jp;
extern const PrepopulatedEngine brave_google;

// Maps BravePrepopulatedEngineID -> PrepopulatedEngine
// LINT.IfChange
inline constexpr auto kBraveEngines =
    base::MakeFixedFlatMap<BravePrepopulatedEngineID,
                           const PrepopulatedEngine*>({
        // SearxGo como primeiro entry — torna-se o default
        {PREPOPULATED_ENGINE_ID_SEARXGO, &searxgo},
        {PREPOPULATED_ENGINE_ID_GOOGLE, &brave_google},
        {PREPOPULATED_ENGINE_ID_YANDEX, &brave_yandex},
        {PREPOPULATED_ENGINE_ID_BING, &brave_bing},
        {PREPOPULATED_ENGINE_ID_NAVER, &naver},
        {PREPOPULATED_ENGINE_ID_DAUM, &daum},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO, &duckduckgo},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE, &duckduckgo_de},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE, &duckduckgo_au_nz_ie},
        {PREPOPULATED_ENGINE_ID_QWANT, &qwant},
        {PREPOPULATED_ENGINE_ID_STARTPAGE, &brave_startpage},
        {PREPOPULATED_ENGINE_ID_ECOSIA, &brave_ecosia},
        {PREPOPULATED_ENGINE_ID_BRAVE, &brave_search},
        {PREPOPULATED_ENGINE_ID_YAHOO_JP, &brave_yahoo_jp},
    });
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

}  // namespace TemplateURLPrepopulateData

#endif  // BRAVE_COMPONENTS_SEARCH_ENGINES_BRAVE_PREPOPULATED_ENGINES_H_
