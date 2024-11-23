################################################################################
# Copyright (c) 2023 Vladislav Trifochkin
#
# This file is part of `lorem-lib`.
#
# Changelog:
#      2023.04.19 Initial version.
################################################################################
project(lorem_ipsum)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pfs::lorem)


