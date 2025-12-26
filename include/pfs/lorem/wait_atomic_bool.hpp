////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.12.10 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <atomic>
#include <chrono>

LOREM__NAMESPACE_BEGIN

class wait_atomic_bool
{
    std::atomic_bool _flag {false};
    std::chrono::milliseconds _time_limit {5000};
    std::chrono::milliseconds _time_quantum {10};

public:
    wait_atomic_bool (std::chrono::milliseconds time_limit = std::chrono::milliseconds{5000}
        , std::chrono::milliseconds time_quantum = std::chrono::milliseconds{10})
        : _time_limit(time_limit)
        , _time_quantum(time_quantum)
    {}

    ~wait_atomic_bool () = default;
    wait_atomic_bool (wait_atomic_bool const &) = delete;
    wait_atomic_bool (wait_atomic_bool &&) = delete;
    wait_atomic_bool & operator = (wait_atomic_bool const &) = delete;
    wait_atomic_bool & operator = (wait_atomic_bool &&) = delete;

public:
    // Avoid return value
    void set ()
    {
        _flag.store(true);
    }

    void reset ()
    {
        _flag.store(false);
    }

    LOREM__EXPORT bool wait ();
};

LOREM__NAMESPACE_END

