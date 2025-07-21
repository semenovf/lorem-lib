////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include "lang_domain.hpp"
#include <memory>
#include <string>

LOREM__NAMESPACE_BEGIN

enum class gender
{
      male = 0
    , female = 1
};

class person
{
public:
    class impl;

private:
    impl const * _d;

public:
    LOREM__EXPORT person (lang_domain ld, gender g);

    /**
     * Random first name if @a index < 0 or a permanent value if @a index >= 0.
     */
    LOREM__EXPORT std::string first_name (int index = -1) const;

    /**
     * Random middle name if @a index < 0 or a permanent value if @a index >= 0.
     * Result may be empty if middle name is not applicable for specified domain.
     */
    LOREM__EXPORT std::string middle_name (int index = -1) const;

    /**
     * Random last name if @a index < 0 or a permanent value if @a index >= 0.
     */
    LOREM__EXPORT std::string last_name (int index = -1) const;

    /**
     * Generates full name according to the language domain traits.
     */
    LOREM__EXPORT std::string full_name (bool last_is_first) const;

    /**
     * Generates full name according to the default language domain traits.
     */
    LOREM__EXPORT std::string full_name () const;

    /**
     * Genarates composition of the random or specifed by index person
     * credentials according to format string @a fm.
     *
     * @param fm Is the format sequence that consist of specificators '%l',
     *       '%f', '%m' and '%%' letters and any characters. E.g. '%l %f %m'
     *       will force to output last name, then first and middle names,
     *       '%f %l' will force to output first name and then last one.
     */
    LOREM__EXPORT std::string format (int index, std::string const & fm) const;
};

LOREM__NAMESPACE_END
