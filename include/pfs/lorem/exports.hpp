////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef LOREM__STATIC
#   ifndef LOREM__EXPORT
#       if _MSC_VER
#           if defined(LOREM__EXPORTS)
#               define LOREM__EXPORT __declspec(dllexport)
#           else
#               define LOREM__EXPORT __declspec(dllimport)
#           endif
#       else
#           define LOREM__EXPORT
#       endif
#   endif
#else
#   define LOREM__EXPORT
#endif // !LOREM__STATIC

