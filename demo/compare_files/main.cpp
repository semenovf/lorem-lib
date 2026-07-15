////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2026.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/compare_files.hpp"
#include <pfs/argvapi.hpp>
#include <pfs/filesystem.hpp>
#include <pfs/fmt.hpp>
#include <pfs/log.hpp>
#include <pfs/stopwatch.hpp>

namespace fs = pfs::filesystem;

static char const * TAG = "LOREM";

std::string const USAGE =
R"(Usage:
    {0} [{{--raw | --sha256}}] FILE FILE
    {0} (-h | --help)

Options:
    -h --help
        Show this help usage.

    --raw
        Compare files for identity byte by byte (default).

    --sha256
        Compare files for identity by SHA256 checksums.
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
    bool useRawComparator = true;

    if (!commandLineIterator.has_more()) {
        print_usage(programName);
        return EXIT_SUCCESS;
    }

    auto x = commandLineIterator.next();

    do {
        if (x.is_option("help") || x.is_option("h")) {
            print_usage(programName);
            return EXIT_SUCCESS;
        } else if (x.is_option("sha256")) {
            useRawComparator = false;
        } else if (x.is_option("raw")) {
            useRawComparator = true;
        } else {
            break;
        }

        x = commandLineIterator.next();
    } while (commandLineIterator.has_more());

    if (!x.is_arg()) {
        LOGE(TAG, "Expected file path");
        return EXIT_FAILURE;
    }

    auto fileA = pfs::utf8_decode_path(x.arg().to_string());
    x = commandLineIterator.next();

    if (!x.is_arg()) {
        LOGE(TAG, "Expected file path");
        return EXIT_FAILURE;
    }

    auto fileB = pfs::utf8_decode_path(x.arg().to_string());

    bool isIdentical = false;

    pfs::stopwatch<> sw;
    try {
        isIdentical = useRawComparator
            ? lorem::files_raw_identical(fileA, fileB)
            : lorem::files_sha256_identical(fileA, fileB);
    } catch (pfs::error const & ex) {
        LOGE(TAG, "Compare files failure: {}", ex.what());
        return EXIT_FAILURE;
    }

    sw.stop();
    LOGI(TAG, "Files are {} ({})", isIdentical ? "idetical" : "NOT idetical", sw.duration());

    return EXIT_SUCCESS;
}

