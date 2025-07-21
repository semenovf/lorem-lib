////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.08.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "lorem/file.hpp"
#include "lorem/utils.hpp"
#include <pfs/assert.hpp>
#include <pfs/expected.hpp>
#include <pfs/i18n.hpp>
#include <pfs/standard_paths.hpp>
#include <pfs/universal_id_ulid.hpp>
#include <pfs/ionik/local_file.hpp>

LOREM__NAMESPACE_BEGIN

namespace fs = pfs::filesystem;

static char random_char_generator (std::size_t)
{
    return static_cast<char>(integer(-127, 128));
}

static char serial_char_generator (std::size_t index)
{
    return static_cast<char>(index % 256);
}

static char zero_char_generator (std::size_t)
{
    return static_cast<char>(0);
}

basic_content_file::basic_content_file (pfs::filesystem::path const & path, std::size_t size
    , char (* char_generator) (std::size_t))
{
    populate(path, size, char_generator);
}

basic_content_file::basic_content_file (std::size_t size, char (* char_generator) (std::size_t))
{
    auto root_dir = pfs::filesystem::standard_paths::temp_folder();
    auto uuid = pfs::generate_uuid();
    fs::path path;
    int attempts = 10;

    do {
        path = root_dir / pfs::utf8_decode_path(to_string(uuid));

        if (fs::exists(path))
            path.clear();
    } while (attempts-- > 0 && path.empty());

    PFS__THROW_UNEXPECTED(!path.empty(), tr::_("Oops! Unable to generate unique file"));

    populate(path, size, char_generator);
}

void basic_content_file::populate (pfs::filesystem::path const & path, std::size_t size
    , char (* char_generator) (std::size_t index))
{
    PFS__THROW_UNEXPECTED(!fs::exists(path), tr::f_("file already exists: {}", path));

    ionik::error err;
    auto file = ionik::local_file::open_write_only(path, ionik::truncate_enum::on, size, & err);

    PFS__THROW_UNEXPECTED(!err, err.what());
    _path = path;

    char buffer [4096];

    for (std::size_t i = 0; i < size;) {
        std::size_t j = 0;

        for (; j < sizeof(buffer) && i < size; j++, i++)
            buffer[j] = char_generator(i);

        file.write(buffer, j);
    }
}

random_content_file::random_content_file (std::size_t size)
    : basic_content_file(size, random_char_generator)
{}

random_content_file::random_content_file (pfs::filesystem::path const & path, std::size_t size)
    : basic_content_file(path, size, random_char_generator)
{}

serial_content_file::serial_content_file (std::size_t size)
    : basic_content_file(size, serial_char_generator)
{}

serial_content_file::serial_content_file (pfs::filesystem::path const & path, std::size_t size)
    : basic_content_file(path, size, serial_char_generator)
{}

zero_content_file::zero_content_file (std::size_t size)
    : basic_content_file(size, zero_char_generator)
{}

zero_content_file::zero_content_file (pfs::filesystem::path const & path, std::size_t size)
    : basic_content_file(path, size, zero_char_generator)
{}

LOREM__NAMESPACE_END
