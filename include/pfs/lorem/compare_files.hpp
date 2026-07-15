////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2026.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <pfs/filesystem.hpp>

LOREM__NAMESPACE_BEGIN

/**
 * Compares files for identity byte by byte.
 *
 * @throws pfs::error if open or read any file failure.
 */
bool files_raw_identical (pfs::filesystem::path const & a, pfs::filesystem::path const & b);

/**
 * Compares files for identity by SHA256 checksums.
 *
 * @throws pfs::error if open or read any file failure.
 */
bool files_sha256_identical (pfs::filesystem::path const & a, pfs::filesystem::path const & b);

LOREM__NAMESPACE_END

