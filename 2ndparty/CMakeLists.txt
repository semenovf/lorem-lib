################################################################################
# Copyright (c) 2025 Vladislav Trifochkin
#
# This file is part of `netty-lib`.
#
# Changelog:
#       2025.08.21 Initial version
################################################################################

if (NOT TARGET pfs::common)
    if (NETTY__DISABLE_FETCH_CONTENT AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/common/.git)
        add_subdirectory(common)
    else()
        set(FETCHCONTENT_UPDATES_DISCONNECTED_COMMON ON)
        message(STATUS "Fetching common ...")
        include(FetchContent)
        FetchContent_Declare(common
            GIT_REPOSITORY https://github.com/semenovf/common-lib.git
            GIT_TAG master
            SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/common)
        FetchContent_MakeAvailable(common)
        message(STATUS "Fetching common complete")
    endif()
endif()

if (NOT TARGET pfs::ionik)
    if (NETTY__DISABLE_FETCH_CONTENT AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/ionik/.git)
        add_subdirectory(ionik)
    else()
        set(FETCHCONTENT_UPDATES_DISCONNECTED_IONIK ON)
        message(STATUS "Fetching pfs::ionik ...")
        include(FetchContent)
        FetchContent_Declare(ionik
            GIT_REPOSITORY https://github.com/semenovf/ionik-lib.git
            GIT_TAG master
            SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ionik)
        FetchContent_MakeAvailable(ionik)
        message(STATUS "Fetching pfs::ionik complete")
    endif()
endif()
