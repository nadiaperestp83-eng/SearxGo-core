// Copyright 2024 The Chromium Authors / SearxGo Authors.
// Use of this source code is governed by a BSD-style license.

#ifndef COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_
#define COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_

namespace prefs {

// URL base da instância SearXNG configurada pelo usuário.
// Padrão: vazio (forçado via build flag SEARXGO_DEFAULT_URL)
inline constexpr char kSearxGoEndpointURL[] = "searxgo.endpoint_url";

// Chave de API da instância SearXNG (opcional).
inline constexpr char kSearxGoAPIKey[]      = "searxgo.api_key";

// Mantém os prefs originais do Chromium abaixo:
inline constexpr char kSyncedDefaultSearchProviderGUID[] =
    "default_search_provider.synced_guid";

inline constexpr char kDefaultSearchProviderEnabled[] =
    "default_search_provider_enabled";

inline constexpr char kSearchProviderOverrides[] =
    "search_provider_overrides";

inline constexpr char kSearchProviderOverridesVersion[] =
    "search_provider_overrides_version";

}  // namespace prefs

#endif  // COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_
