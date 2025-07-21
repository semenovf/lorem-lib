////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2025.08.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/file.hpp"
#include <pfs/argvapi.hpp>
#include <pfs/filesystem.hpp>
#include <pfs/fmt.hpp>
#include <pfs/log.hpp>
#include <pfs/string_view.hpp>
#include <pfs/integer.hpp>
#include <system_error>
#include <string>

namespace fs = pfs::filesystem;

static char const * TAG = "LOREM";

std::string const USAGE =
R"(Usage:
    {0} {{--serial | --random | --zero}} --size=NUMBER
    {0} (-h | --help)

Options:
    -h --help
        Show this help usage.

    --serial
        Generate content with serial chars 0,1,2,3,...

    --random
        Generate content with random chars (default).

    --zero
        Generate content with zero chars.

    --size=NUMBER
        File size in bytes.
)";

void print_usage (pfs::filesystem::path const & programName
    , std::string const & errorString = std::string{})
{
    std::FILE * out = stdout;

    if (!errorString.empty()) {
        out = stderr;
        LOGE(TAG, "{}", errorString);
    }

    fmt::println(out, USAGE, programName);
}

int main (int argc, char * argv[])
{
    auto commandLine = pfs::make_argvapi(argc, argv);
    auto programName = commandLine.program_name();
    auto commandLineIterator = commandLine.begin();
    pfs::string_view expectedValueOpt;
    bool random_content = true;
    bool serial_content = false;
    bool zero_content = false;
    std::size_t size {0};

    if (!commandLineIterator.has_more()) {
        print_usage(programName);
        return EXIT_SUCCESS;
    }

    while (commandLineIterator.has_more()) {
        auto x = commandLineIterator.next();

        if (x.is_option("help") || x.is_option("h")) {
            print_usage(programName);
            return EXIT_SUCCESS;
        } else if (x.is_option("random")) {
            random_content = true;
            serial_content = false;
            zero_content = false;
        } else if (x.is_option("serial")) {
            random_content = false;
            serial_content = true;
            zero_content = false;
        } else if (x.is_option("zero")) {
            random_content = false;
            serial_content = false;
            zero_content = true;
        } else if (x.is_option("size")) {
            if (!x.has_arg()) {
                expectedValueOpt = x.optname();
                break;
            }

            std::error_code ec;
            size = pfs::to_integer<std::size_t>(x.arg().begin(), x.arg().end(), ec);

            if (ec) {
                LOGE(TAG, "Bad number value for: {}", x.optname());
                return EXIT_FAILURE;
            }
        } else {
            LOGE(TAG, "Bad option: {}. Try --help option.", x.optname());
            return EXIT_FAILURE;
        }
    }

    if (!expectedValueOpt.empty()) {
        LOGE(TAG, "Expected value for: {}", expectedValueOpt);
        return EXIT_FAILURE;
    }

    if (size == 0) {
        LOGE(TAG, "Size mus be more than zero");
        return EXIT_FAILURE;
    }

    if (random_content) {
        lorem::random_content_file file {size};
        LOGD(TAG, "Random content saved in: {} ({} bytes)", file.path(), fs::file_size(file.path()));
    } else if (serial_content) {
        lorem::serial_content_file file {size};
        LOGD(TAG, "Serial content saved in: {} ({} bytes)", file.path(), fs::file_size(file.path()));
    } else if (zero_content) {
        lorem::zero_content_file file {size};
        LOGD(TAG, "Zero content saved in: {} ({} bytes)", file.path(), fs::file_size(file.path()));
    }

    return EXIT_SUCCESS;
}

