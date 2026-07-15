////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2026.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "lorem/compare_files.hpp"
#include <pfs/error.hpp>
#include <pfs/sha256.hpp>
#include <fstream>
#include <vector>

LOREM__NAMESPACE_BEGIN

namespace fs = pfs::filesystem;

bool files_raw_identical (pfs::filesystem::path const & a, pfs::filesystem::path const & b)
{
    constexpr std::size_t kBUFSZ = 4096;

    if (fs::file_size(a) != fs::file_size(b))
        return false;

    std::vector<std::uint8_t> buffer_a(kBUFSZ);
    std::vector<std::uint8_t> buffer_b(kBUFSZ);
    std::ifstream ifs_a;
    std::ifstream ifs_b;

    try {
        ifs_a.exceptions(std::ios::failbit | std::ios::badbit);
        ifs_b.exceptions(std::ios::failbit | std::ios::badbit);

        ifs_a.open(pfs::utf8_encode_path(a), std::ios::binary);
        ifs_b.open(pfs::utf8_encode_path(b), std::ios::binary);

        while (ifs_a.good() && ifs_b.good()) {
            ifs_a.read(reinterpret_cast<char *>(buffer_a.data()), buffer_a.size());
            ifs_b.read(reinterpret_cast<char *>(buffer_b.data()), buffer_b.size());

            std::streamsize sz_a = ifs_a.gcount();
            std::streamsize sz_b = ifs_b.gcount();

            if (sz_a != sz_b)
                return false;

            if (!std::equal(buffer_a.data(), buffer_a.data() + sz_a, buffer_b.data()))
                return false;
        }
    } catch (std::ios_base::failure ex) {
        throw pfs::error {ex.code(), ex.what()};
    } catch (...) {
        throw pfs::error {make_error_code(pfs::errc::unexpected_error)};
    }

    return true;
}

bool files_sha256_identical (pfs::filesystem::path const & a, pfs::filesystem::path const & b)
{
    auto digest_a = pfs::crypto::sha256::digest(a);
    auto digest_b = pfs::crypto::sha256::digest(b);

    if (!is_valid(digest_a))
        return false;

    if (!is_valid(digest_b))
        return false;

    return digest_a == digest_b;
}

LOREM__NAMESPACE_END
