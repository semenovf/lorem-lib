////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/utils.hpp"
#include "pfs/unicode/char.hpp"
#include "pfs/unicode/utf8_iterator.hpp"
#include <algorithm>
#include <random>
#include <system_error>
#include <utility>

namespace lorem {

using random_engine_t = std::mt19937;

inline auto engine () -> random_engine_t
{
    static std::random_device __rd; // Will be used to obtain a seed for the random number engine
    return random_engine_t{__rd()}; // Standard mersenne_twister_engine seeded with rd()
}

int integer (int from, int to)
{
    if (from == to)
        return from;

    std::uniform_int_distribution<int> distrib{from, to};
    auto rnd = engine();
    return distrib(rnd);
}

unsigned int unsigned_integer (unsigned int from, unsigned int to)
{
    if (from == to)
        return from;

    std::uniform_int_distribution<unsigned int> distrib{from, to};
    auto rnd = engine();
    return distrib(rnd);
}

unsigned int index (unsigned int size)
{
    if (size == 0)
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));

    std::uniform_int_distribution<unsigned int> distrib{0, size - 1};
    auto rnd = engine();
    return distrib(rnd);
}

unsigned int index (unsigned int size, int requested_index)
{
    if (size == 0)
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));

    return (requested_index >= 0)
        ? requested_index % size
        : unsigned_integer(0, size - 1);
}

bool boolean ()
{
    return !!integer(0, 1);
}

std::string greek_letter ()
{
    static char const * __greek_letters[] = {"alpha", "beta", "gamma", "delta"
        , "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"
        , "nu", "xi", "omicron", "pi", "rho", "sigma", "tau", "upsilon"
        , "phi", "chi", "psi", "omega"
    };

    static std::uniform_int_distribution<int> __distrib{ 0
        , sizeof(__greek_letters) / sizeof(__greek_letters[0]) - 1};

    auto rnd = engine();
    auto index = __distrib(rnd);
    return __greek_letters[index];
}

std::string capitalize (std::string const & word)
{
    using utf8_iterator = pfs::unicode::utf8_iterator<std::string::const_iterator>;

    if (word.empty())
        return word;

    std::string result;
    pfs::unicode::utf8_output_iterator<std::back_insert_iterator<std::string>> out(std::back_inserter(result));
    auto it = utf8_iterator::begin(word.cbegin(), word.cend());

    // Output first capitalized character
    *out++ = pfs::unicode::to_upper(*it);
    ++it;

    // Copy tail
    std::copy(it.base(), it.end().base(), std::back_inserter(result));

    return result;
}

} // namespace lorem
