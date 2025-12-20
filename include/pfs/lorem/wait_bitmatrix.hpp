////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.12.09 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "namespace.hpp"
#include <pfs/bitmatrix.hpp>
#include <pfs/countdown_timer.hpp>
#include <pfs/synchronized.hpp>
#include <chrono>
#include <cstdint>

LOREM__NAMESPACE_BEGIN

/**
 * Monitors until the matrix is ​​filled.
 */
template <std::size_t Rows, std::size_t Cols = Rows>
class wait_bitmatrix
{
    using bitmatrix_type = pfs::bitmatrix<Rows, Cols>;

private:
    pfs::synchronized<bitmatrix_type> _m;
    std::chrono::milliseconds _time_limit {5000};
    std::chrono::milliseconds _time_quantum {10};

public:
    wait_bitmatrix (std::chrono::milliseconds time_limit = std::chrono::milliseconds{5000}
        , std::chrono::milliseconds time_quantum = std::chrono::milliseconds{10})
        : _time_limit(time_limit)
        , _time_quantum(time_quantum)
    {}

    ~wait_bitmatrix () = default;

    wait_bitmatrix (wait_bitmatrix const &) = delete;
    wait_bitmatrix (wait_bitmatrix &&) = delete;
    wait_bitmatrix & operator = (wait_bitmatrix const &) = delete;
    wait_bitmatrix & operator = (wait_bitmatrix &&) = delete;

public:
    /**
     *  Sets the bit at position @a row,@a col to @c true.
     *
     *  @throws std::out_of_range if @a row or @a col or both does not correspond to a valid cell.
     */
    wait_bitmatrix & set (std::size_t row, std::size_t col, bool value = true)
    {
        _m.wlock()->set(row, col, value);
        return *this;
    }

    bitmatrix_type value () const
    {
        return _m.unsafe();
    }

    bool operator () ()
    {
        pfs::countdown_timer<std::milli> timer {_time_limit};
        std::size_t count = Rows * Cols;

        while (_m.rlock()->count() < count && timer.remain_count() > 0)
            std::this_thread::sleep_for(_time_quantum);

        return _m.rlock()->count() == count;
    }
};

LOREM__NAMESPACE_END
