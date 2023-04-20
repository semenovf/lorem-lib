////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "pfs/lorem/person.hpp"
#include "pfs/lorem/utils.hpp"
#include <memory>
#include <string>

namespace lorem {

class person::impl
{
public:
    virtual std::string first_name (int index) const { (void)index; return ""; }
    virtual std::string middle_name (int index) const { (void)index; return ""; }
    virtual std::string last_name (int index) const { (void)index; return ""; }
    virtual std::string full_name (bool last_is_first) const { (void)last_is_first; return ""; }
    virtual std::string full_name () const { return ""; }
};

} // namespace lorem
