////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/fmt.hpp"
#include "pfs/log.hpp"
#include "pfs/string_view.hpp"
#include "pfs/integer.hpp"
#include "pfs/lorem/lorem_ipsum.hpp"
#include "pfs/lorem/utils.hpp"
// #include "pfs/string_view.hpp"
// #include "pfs/netty/startup.hpp"
// #include <algorithm>
// #include <map>
#include <string>
// #include <vector>
// #include <cstdlib>
//
static char const * TAG = "LOREM";

// #include "types.hpp"
// #include "client_routine.hpp"
// #include "server_routine.hpp"

static struct program_context {
    std::string program;
} __pctx;

static void print_usage ()
{
    fmt::print(stdout, "Usage\n\t{} [OPTIONS]\n"
        , __pctx.program);
    fmt::print(stdout, "Options:\n");
    fmt::print(stdout, "\t\t--para-count=NUMBER\n");
    fmt::print(stdout, "\t\t--sentence-count=NUMBER\n");
    fmt::print(stdout, "\t\t--word-count=NUMBER\n");
}

// template <typename Iter>
// static std::string concat (Iter first, Iter last, std::string const & separator)
// {
//     std::string result;
//
//     if (first != last) {
//         result += *first;
//         ++first;
//     }
//
//     for (; first != last; ++first) {
//         result += separator;
//         result += *first;
//     }
//
//     return result;
// }

int main (int argc, char * argv[])
{
    __pctx.program = argv[0];

    bool capitalize = false;
    lorem::lorem_ipsum ipsum;

    if (argc == 1) {
        print_usage();
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (pfs::string_view{"-h"} == argv[i] || pfs::string_view{"--help"} == argv[i]) {
            print_usage();
            return EXIT_SUCCESS;
        } else if (pfs::starts_with(pfs::string_view{argv[i]}, "--para-count=")) {
            auto str = std::string{argv[i] + 13};
            std::error_code ec;
            auto pc = pfs::to_integer<unsigned int>(str.cbegin(), str.cend(), ec);

            if (ec) {
                LOGE(TAG, "Bad value for `--para-count`");
                return EXIT_FAILURE;
            }

            ipsum.set_paragraph_count(pc);
        } else if (pfs::starts_with(pfs::string_view{argv[i]}, "--sentence-count=")) {
            auto str = std::string{argv[i] + 17};
            std::error_code ec;
            auto sc = pfs::to_integer<unsigned int>(str.cbegin(), str.cend(), ec);

            if (ec) {
                LOGE(TAG, "Bad value for `--sentence-count`");
                return EXIT_FAILURE;
            }

            ipsum.set_sentence_count(sc);
        } else if (pfs::starts_with(pfs::string_view{argv[i]}, "--word-count=")) {
            auto str = std::string{argv[i] + 13};
            std::error_code ec;
            auto wc = pfs::to_integer<unsigned int>(str.cbegin(), str.cend(), ec);

            if (ec) {
                LOGE(TAG, "Bad value for `--word-count`");
                return EXIT_FAILURE;
            }

            ipsum.set_word_count(wc);
        } else {
            auto arglen = std::strlen(argv[i]);

            if (arglen > 0 && argv[i][0] == '-') {
                LOGE(TAG, "Bad option: {}", argv[i]);
                return EXIT_FAILURE;
            }

            if (capitalize) {
                fmt::print("{}\n", lorem::capitalize(std::string{argv[i]}));
            }
        }
    }

    auto paras = ipsum();
    char const * para_delim = "";

    for (auto const & para: paras) {
        fmt::print(para_delim);

        for (auto const & sentence: para) {
            fmt::print(sentence);
            fmt::print("\n");
        }

        para_delim = "\n";
    }

    return EXIT_SUCCESS;
}
