////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.12.10 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "lorem/wait_atomic_bool.hpp"
#include <pfs/countdown_timer.hpp>
#include <thread>

LOREM__NAMESPACE_BEGIN

bool wait_atomic_bool::wait ()
{
    pfs::countdown_timer<std::milli> timer {_time_limit};

    while (!_flag.load() && timer.remain_count() > 0)
        std::this_thread::sleep_for(_time_quantum);

    return _flag.load() == true;
}

LOREM__NAMESPACE_END
