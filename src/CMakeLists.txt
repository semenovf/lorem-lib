################################################################################
# Copyright (c) 2023-2025 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#       2023.04.19 Initial version (library.cmake).
#       2024.11.23 Removed `portable_target` dependency.
#       2025.12.02 Moved from root directory and renamed from library.cmake.
################################################################################
project(lorem LANGUAGES C CXX)

option(LOREM__BUILD_SHARED "Enable build shared library" OFF)

if (BUILD_SHARED_LIBS AND NOT LOREM__BUILD_STATIC)
    add_library(lorem)
    target_compile_definitions(lorem PUBLIC LOREM__EXPORTS)
else()
    add_library(lorem STATIC)
    target_compile_definitions(lorem PUBLIC LOREM__STATIC)
endif()

add_library(pfs::lorem ALIAS lorem)

target_sources(lorem PRIVATE
    file.cpp
    lang_domain.cpp
    lorem_ipsum.cpp
    person.cpp
    utils.cpp
    wait_atomic_bool.cpp
    wait_atomic_counter.cpp
    lang_domains/en_US/person.cpp
    lang_domains/ru_RU/person.cpp)

target_include_directories(lorem
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include/pfs)

target_link_libraries(lorem PUBLIC pfs::common PRIVATE pfs::ionik)
