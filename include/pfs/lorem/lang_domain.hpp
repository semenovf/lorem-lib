////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "namespace.hpp"
#include <pfs/optional.hpp>
#include <string>

LOREM__NAMESPACE_BEGIN

enum class lang_domain
{
      en_US
    , ru_RU
};

pfs::optional<lang_domain> lang_domain_from_string (std::string const & s);

LOREM__NAMESPACE_END
