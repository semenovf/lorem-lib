################################################################################
# Copyright (c) 2023-2026 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#       2023.04.19 Initial version.
#       2024.05.21 Fixed `portable-target` path.
#                  Added LOREM__ENABLE_PROFILER option.
#       2024.11.23 Up to C++14 standard.
#                  Removed `portable_target` dependency.
#       2026.07.15 Removed setting CMAKE_*_OUTPUT_DIRECTORY.
################################################################################
cmake_minimum_required (VERSION 3.19)
project(lorem-ALL LANGUAGES C CXX)

option(LOREM__BUILD_STRICT "Build with strict policies: C++ standard required, C++ extension is OFF etc" ON)
option(LOREM__BUILD_DEMO "Build examples/demo" OFF)
option(LOREM__BUILD_STATIC "Force build static library" OFF)

if (LOREM__BUILD_STRICT)
    if (NOT CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 14)
    endif()

    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++XX rather than -std=gnu++XX
endif()

add_subdirectory(2ndparty)
add_subdirectory(src)

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
