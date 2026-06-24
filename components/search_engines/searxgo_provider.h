// Copyright 2024 SearxGo Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license.

#ifndef COMPONENTS_SEARCH_ENGINES_SEARXGO_PROVIDER_H_
#define COMPONENTS_SEARCH_ENGINES_SEARXGO_PROVIDER_H_

#include <memory>
#include <string>

#include "components/search_engines/template_url_data.h"

namespace searxgo {

// Prepopulate ID reservado para SearxGo (fora do range Chromium 1-999)
inline constexpr int kSearxGoPrepopulateId = 9000;

// Cria o TemplateURLData do SearXNG com base_url e api_key lidos de prefs.
// base_url  — ex: "https://search.example.com"
// api_key   — chave configurada na instância SearXNG (pode ser vazio)
std::unique_ptr<TemplateURLData> CreateSearxGoEngine(
    const std::string& base_url,
    const std::string& api_key);

// Retorna true se o engine de id |prepopulate_id| é o SearxGo
bool IsSearxGoEngine(int prepopulate_id);

}  // namespace searxgo

#endif  // COMPONENTS_SEARCH_ENGINES_SEARXGO_PROVIDER_H_
