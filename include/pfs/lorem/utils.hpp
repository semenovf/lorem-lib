////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <string>

LOREM__NAMESPACE_BEGIN

/**
 * Returns random integer in range [@a from, @a to].
 */
LOREM__EXPORT int integer (int from, int to);
LOREM__EXPORT unsigned int unsigned_integer (unsigned int from, unsigned int to);

/**
 * Returns random index value in range [0, @a size).
 *
 * @throws std::system_error {std::errc::invalid_argument} if @a size == 0.
 */
LOREM__EXPORT unsigned int index (unsigned int size);

/**
 * Returns random index value if @a requested_index less than zero or
 * @a requested_index modulo @a collection_size.
 */
LOREM__EXPORT unsigned int index (unsigned int size, int requested_index);

/**
 * Returns random boolean value.
 */
LOREM__EXPORT bool boolean ();

/**
 * Returns random Greek letter name: alpha, beta, gamma, delta, etc.
 */
LOREM__EXPORT std::string greek_letter ();

/**
 * Capitalizes first letter.
 */
LOREM__EXPORT std::string capitalize (std::string const & word);

LOREM__NAMESPACE_END
