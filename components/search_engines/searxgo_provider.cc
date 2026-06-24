// Copyright 2024 SearxGo Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license.

#include "components/search_engines/searxgo_provider.h"

#include <memory>
#include <string>

#include "base/strings/utf_string_conversions.h"
#include "components/search_engines/template_url_data.h"
#include "url/gurl.h"

namespace searxgo {

std::unique_ptr<TemplateURLData> CreateSearxGoEngine(
    const std::string& base_url,
    const std::string& api_key) {
  auto data = std::make_unique<TemplateURLData>();

  data->SetShortName(u"SearxGo");
  data->SetKeyword(u"searxgo");
  data->prepopulate_id = kSearxGoPrepopulateId;

  // Monta URL de busca. Se api_key não estiver vazio, injeta como query param.
  // Ajuste o param name conforme sua config SearXNG (padrão: "token").
  std::string search_url;
  if (api_key.empty()) {
    search_url = base_url + "/search?q={searchTerms}&format=json";
  } else {
    search_url = base_url +
        "/search?q={searchTerms}&format=json&token=" + api_key;
  }

  data->SetURL(search_url);

  // SearXNG não expõe endpoint de sugestões por padrão — deixa vazio
  data->suggestions_url = std::string();
  data->image_url = std::string();
  data->new_tab_url = std::string();

  // Favicon da instância
  data->favicon_url = GURL(base_url + "/favicon.ico");

  // Força engine como safe search desativado (controlado pela instância)
  data->safe_for_autoreplace = false;

  return data;
}

bool IsSearxGoEngine(int prepopulate_id) {
  return prepopulate_id == kSearxGoPrepopulateId;
}

}  // namespace searxgo
