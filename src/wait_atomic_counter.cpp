////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.12.02 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "lorem/wait_atomic_counter.hpp"
#include <pfs/countdown_timer.hpp>
#include <thread>

LOREM__NAMESPACE_BEGIN

template <typename UIntT>
bool wait_atomic_counter<UIntT>::operator () ()
{
    pfs::countdown_timer<std::milli> timer {_time_limit};

    while (_counter.load() < _limit && timer.remain_count() > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds{10});

    return _counter.load() == _limit;
}

template class wait_atomic_counter<std::uint8_t>;
template class wait_atomic_counter<std::uint16_t>;
template class wait_atomic_counter<std::uint32_t>;
template class wait_atomic_counter<std::uint64_t>;

LOREM__NAMESPACE_END
