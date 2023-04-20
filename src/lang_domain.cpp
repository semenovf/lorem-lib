////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/lang_domain.hpp"
#include <map>

namespace lorem {

pfs::optional<lang_domain> lang_domain_from_string (std::string const & s)
{
    static const std::map<std::string, lang_domain> __mapping = {
          { "ru_RU", lang_domain::ru_RU }
        , { "en_US", lang_domain::en_US }
    };

    auto pos = __mapping.find(s);
    return pos == __mapping.end() ? pfs::nullopt : pfs::make_optional(pos->second);
}

} // namespace lorem
