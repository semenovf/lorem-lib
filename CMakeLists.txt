################################################################################
# Copyright (c) 2023-2024 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#       2023.04.19 Initial version.
#       2024.05.21 Fixed `portable-target` path.
#                  Added LOREM__ENABLE_PROFILER option.
#       2024.11.23 Up to C++14 standard.
#                  Removed `portable_target` dependency.
################################################################################
cmake_minimum_required (VERSION 3.19)
project(lorem-ALL LANGUAGES CXX C)

option(LOREM__BUILD_STRICT "Build with strict policies: C++ standard required, C++ extension is OFF etc" ON)
option(LOREM__BUILD_DEMO "Build examples/demo" OFF)

if (LOREM__BUILD_STRICT)
    if (NOT CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 14)
    endif()

    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++XX rather than -std=gnu++XX
endif()

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

include(${CMAKE_CURRENT_LIST_DIR}/library.cmake)

if (LOREM__BUILD_DEMO)
    add_subdirectory(demo)
endif()

include(GNUInstallDirs)

install(TARGETS lorem
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
