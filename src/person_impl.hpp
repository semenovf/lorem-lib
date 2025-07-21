////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "lorem/person.hpp"
#include "lorem/utils.hpp"
#include <memory>
#include <string>

LOREM__NAMESPACE_BEGIN

class person::impl
{
public:
    virtual std::string first_name (int index) const { (void)index; return ""; }
    virtual std::string middle_name (int index) const { (void)index; return ""; }
    virtual std::string last_name (int index) const { (void)index; return ""; }
    virtual std::string full_name (bool last_is_first) const { (void)last_is_first; return ""; }
    virtual std::string full_name () const { return ""; }
};

LOREM__NAMESPACE_END
