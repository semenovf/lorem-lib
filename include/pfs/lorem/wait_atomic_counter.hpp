////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.12.02 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <atomic>
#include <chrono>
#include <cstdint>

LOREM__NAMESPACE_BEGIN

template <typename UIntT>
class wait_atomic_counter
{
    std::atomic<UIntT> _counter {0};
    UIntT _limit {0};
    std::chrono::milliseconds _time_limit {5000};
    std::chrono::milliseconds _time_quantum {10};

public:
    wait_atomic_counter (UIntT limit, std::chrono::milliseconds time_limit = std::chrono::milliseconds{5000}
        , std::chrono::milliseconds time_quantum = std::chrono::milliseconds{10})
        : _limit(limit)
        , _time_limit(time_limit)
        , _time_quantum(time_quantum)
    {}

    ~wait_atomic_counter () = default;
    wait_atomic_counter (wait_atomic_counter const &) = delete;
    wait_atomic_counter (wait_atomic_counter &&) = delete;
    wait_atomic_counter & operator = (wait_atomic_counter const &) = delete;
    wait_atomic_counter & operator = (wait_atomic_counter &&) = delete;

public:
    // Avoid return value
    void operator ++ ()
    {
        ++_counter;
    }

    void operator ++ (int)
    {
        _counter++;
    }

    UIntT value () const
    {
        return _counter.load();
    }

    LOREM__EXPORT bool wait ();
};

using wait_atomic_counter8  = wait_atomic_counter<std::uint8_t>;
using wait_atomic_counter16 = wait_atomic_counter<std::uint16_t>;
using wait_atomic_counter32 = wait_atomic_counter<std::uint32_t>;
using wait_atomic_counter64 = wait_atomic_counter<std::uint64_t>;

LOREM__NAMESPACE_END
