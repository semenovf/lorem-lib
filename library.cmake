################################################################################
# Copyright (c) 2023-2024 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#       2023.04.19 Initial version.
#       2024.11.23 Removed `portable_target` dependency.
################################################################################
cmake_minimum_required (VERSION 3.19)
project(lorem LANGUAGES C CXX)

option(LOREM__BUILD_SHARED "Enable build shared library" OFF)

if (LOREM__BUILD_SHARED)
    add_library(lorem SHARED)
    target_compile_definitions(lorem PRIVATE LOREM__EXPORTS)
else()
    add_library(lorem STATIC)
    target_compile_definitions(lorem PRIVATE LOREM__STATIC)
endif()

add_library(pfs::lorem ALIAS lorem)

if (NOT TARGET pfs::common)
    set(FETCHCONTENT_UPDATES_DISCONNECTED_COMMON ON)

    include(FetchContent)
    FetchContent_Declare(common
        GIT_REPOSITORY https://github.com/semenovf/common-lib.git
        GIT_TAG master
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/2ndparty/common
        SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/2ndparty/common)
    FetchContent_MakeAvailable(common)
endif()

target_sources(lorem PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lorem_ipsum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/person.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domains/en_US/person.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domains/ru_RU/person.cpp)
target_include_directories(lorem PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(lorem PUBLIC pfs::common)
