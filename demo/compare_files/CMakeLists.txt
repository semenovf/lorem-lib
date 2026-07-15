################################################################################
# Copyright (c) 2026 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#      2026.07.15 Initial version.
################################################################################
project(compare_files)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pfs::lorem)
