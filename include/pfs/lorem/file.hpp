////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <pfs/filesystem.hpp>
#include <cstdint>

LOREM__NAMESPACE_BEGIN

class basic_content_file
{
    pfs::filesystem::path _path;

public:
    LOREM__EXPORT basic_content_file (std::size_t size, char (* char_generator) (std::size_t));
    LOREM__EXPORT basic_content_file (pfs::filesystem::path const & path, std::size_t size
        , char (* char_generator) (std::size_t));

public:
    pfs::filesystem::path path () const noexcept
    {
        return _path;
    }

private:
    void populate (pfs::filesystem::path const & path, std::size_t size
        , char (* char_generator) (std::size_t index));
};

class random_content_file: public basic_content_file
{
public:
    LOREM__EXPORT random_content_file (std::size_t size);
    LOREM__EXPORT random_content_file (pfs::filesystem::path const & path, std::size_t size);
};

class serial_content_file: public basic_content_file
{
public:
    LOREM__EXPORT serial_content_file (std::size_t size);
    LOREM__EXPORT serial_content_file (pfs::filesystem::path const & path, std::size_t size);
};

class zero_content_file: public basic_content_file
{
public:
    LOREM__EXPORT zero_content_file (std::size_t size);
    LOREM__EXPORT zero_content_file (pfs::filesystem::path const & path, std::size_t size);
};

LOREM__NAMESPACE_END
