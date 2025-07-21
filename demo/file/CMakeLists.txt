################################################################################
# Copyright (c) 2025 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#      2025.08.21 Initial version.
################################################################################
project(file)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pfs::lorem)
