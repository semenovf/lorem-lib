################################################################################
# Copyright (c) 2023 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#      2023.04.19 Initial version.
################################################################################
cmake_minimum_required (VERSION 3.11)
project(lorem LANGUAGES C CXX)

option(LOREM__BUILD_SHARED "Enable build shared library" OFF)
option(LOREM__BUILD_STATIC "Enable build static library" ON)

if (NOT PORTABLE_TARGET__CURRENT_PROJECT_DIR)
    set(PORTABLE_TARGET__CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if (NOT TARGET pfs::common)
    portable_target(INCLUDE_PROJECT ${CMAKE_CURRENT_LIST_DIR}/2ndparty/common/library.cmake)
endif()

if (LOREM__BUILD_SHARED)
    portable_target(ADD_SHARED ${PROJECT_NAME} ALIAS pfs::lorem EXPORTS LOREM__EXPORTS)
    list(APPEND _lorem__targets ${PROJECT_NAME})
endif()

if (LOREM__BUILD_STATIC)
    set(STATIC_PROJECT_NAME ${PROJECT_NAME}-static)
    portable_target(ADD_STATIC ${STATIC_PROJECT_NAME} ALIAS pfs::lorem::static EXPORTS LOREM__STATIC)
    list(APPEND _lorem__targets ${STATIC_PROJECT_NAME})
endif()

list(APPEND _lorem__sources
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lorem_ipsum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/person.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domains/en_US/person.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/lang_domains/ru_RU/person.cpp)

foreach(_target IN LISTS _lorem__targets)
    portable_target(SOURCES ${_target} ${_lorem__sources})
    portable_target(INCLUDE_DIRS ${_target} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/include/pfs)
    portable_target(LINK ${_target} PUBLIC pfs::common)
endforeach()
