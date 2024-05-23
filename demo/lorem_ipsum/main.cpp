////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/argvapi.hpp"
#include "pfs/fmt.hpp"
#include "pfs/log.hpp"
#include "pfs/string_view.hpp"
#include "pfs/integer.hpp"
#include "pfs/lorem/lang_domain.hpp"
#include "pfs/lorem/lorem_ipsum.hpp"
#include "pfs/lorem/person.hpp"
#include "pfs/lorem/utils.hpp"
#include <stdexcept>
#include <string>

static char const * TAG = "LOREM";

static struct program_context {
    std::string program;
} __pctx;

std::string const USAGE =
R"(Usage:
    {0} ipsum [--para-count=NUMBER]
        [--sentence-count=NUMBER]
        [--word-count=NUMBER]
    {0} person [--lang-domain=LANG] [--gender=GENDER]
        [--count=NUMBER] [--format=FORMAT | --full-name=TYPE]
    {0} (-h | --help)

Options:
    -h --help
        Show this screen.

IPSUM options:

    --para-count=NUMBER
        Number of paragraphs.

    --sentence-count=NUMBER
        Number of sentences in a paragraph.

    --word-count=NUMBER
        Number of words in a sentence.

    --orig
        Begin with original Lorem ipsum paragraph.

PERSON options:

    --lang-domain=LANG
        Language domain (ru_RU, en_US, etc).

    --gender=GENDER
        Gender ('m' - fo male, 'f' - for female).

    --count=NUMBER
        Number of person names to output.

    --format=FORMAT
        Format to output person name. Use '%l', '%f', '%m' specificators to
        replace them with last, first and middle names respectively in the
        resulting output. Use '%%' to output letter '%'.

    --full-name=TYPE
        Output full name according to the language domain traits with last name
        at the beginning (TYPE='last'), or first name at the beginning
        (TYPE='first').
)";

void print_usage (pfs::filesystem::path const & programName
    , std::string const & errorString = std::string{})
{
    std::FILE * out = stdout;

    if (!errorString.empty()) {
        out = stderr;
        fmt::println(out, "Error: {}", errorString);
    }

    fmt::println(out, USAGE, programName);
}

template <typename CommandLineIterator>
int ipsum_action (CommandLineIterator commandLineIterator)
{
    lorem::lorem_ipsum ipsum;

    if (commandLineIterator.has_more()) {
        while (commandLineIterator.has_more()) {
            auto x = commandLineIterator.next();

            if (x.is_option("para-count")
                || x.is_option("sentence-count")
                || x.is_option("word-count")) {

                if (!x.has_arg()) {
                    fmt::println(stderr, "Expected number for: {}", x.optname());
                    return EXIT_FAILURE;
                }

                std::error_code ec;
                auto n = pfs::to_integer<unsigned int>(x.arg().begin(), x.arg().end(), ec);

                if (ec) {
                    fmt::println(stderr, "Bad number value for: {}", x.optname());
                    return EXIT_FAILURE;
                }

                if (x.is_option("para-count"))
                    ipsum.set_paragraph_count(n);
                else if (x.is_option("sentence-count"))
                    ipsum.set_sentence_count(n);
                else if (x.is_option("word-count"))
                    ipsum.set_word_count(n);
            } else if (x.is_option("orig")) {
                ipsum.begin_with_orig_paragraph(true);
            } else {
                fmt::println(stderr, "Bad argument. Try --help option.");
                return EXIT_FAILURE;
            }
        }
    }

    ipsum.print();

    return EXIT_SUCCESS;
}

template <typename CommandLineIterator>
int person_action (CommandLineIterator commandLineIterator)
{
    pfs::optional<lorem::lang_domain> ld {lorem::lang_domain::en_US};
    auto gender = lorem::gender::male;
    int count = 1;
    std::string full_name;
    std::string format;
    pfs::string_view expectedValueOpt;

    if (commandLineIterator.has_more()) {
        while (commandLineIterator.has_more()) {
            auto x = commandLineIterator.next();

            if (x.is_option("lang-domain")) {
                if (!x.has_arg()) {
                    expectedValueOpt = x.optname();
                    break;
                }

                ld = lorem::lang_domain_from_string(pfs::to_string(x.arg()));
            } else if (x.is_option("gender")) {
                if (!x.has_arg()) {
                    expectedValueOpt = x.optname();
                    break;
                }

                if (x.arg() == "m") {
                    gender = lorem::gender::male;
                } else if (x.arg() == "f") {
                    gender = lorem::gender::female;
                } else {
                    fmt::println(stderr, "Bad gender value");
                    return EXIT_FAILURE;
                }
            } else if (x.is_option("count")) {
                if (!x.has_arg()) {
                    expectedValueOpt = x.optname();
                    break;
                }

                std::error_code ec;
                count = pfs::to_integer<unsigned int>(x.arg().begin(), x.arg().end(), ec);

                if (ec) {
                    fmt::println(stderr, "Bad number value for: {}", x.optname());
                    return EXIT_FAILURE;
                }
            } else if (x.is_option("format")) {
                if (!x.has_arg()) {
                    expectedValueOpt = x.optname();
                    break;
                }

                format = pfs::to_string(x.arg());
            } else if (x.is_option("full-name")) {
                if (!x.has_arg()) {
                    expectedValueOpt = x.optname();
                    break;
                }

                full_name = pfs::to_string(x.arg());

                if (!(full_name == "last" || full_name == "first")) {
                    fmt::println(stderr, "Bad full name");
                    return EXIT_FAILURE;
                }
            }
        }

        if (!expectedValueOpt.empty()) {
            fmt::println(stderr, "Expected value for: {}", expectedValueOpt);
            return EXIT_FAILURE;
        }
    }

    lorem::person person {*ld, gender};

    while (count-- > 0) {
        if (!format.empty()) {
            fmt::println("{}", person.format(-1, format));
        } else {
            if ((!full_name.empty())) {
                if (full_name == "last")
                    fmt::println("{}", person.full_name(true));
                else
                    fmt::println("{}", person.full_name(false));
            } else {
                fmt::println("{}", person.full_name());
            }
        }
    }

    return EXIT_SUCCESS;
}

int main (int argc, char * argv[])
{
    auto commandLine = pfs::make_argvapi(argc, argv);
    auto programName = commandLine.program_name();
    auto commandLineIterator = commandLine.begin();

    if (commandLineIterator.has_more()) {
        auto x = commandLineIterator.next();

        if (x.is_option("help") || x.is_option("h")) {
            print_usage(programName);
            return EXIT_SUCCESS;
        } else {
            if (x.is_arg()) {
                auto action = x.arg();

                if (action == "ipsum") {
                    return ipsum_action(commandLineIterator);
                } else if (action == "person") {
                    return person_action(commandLineIterator);
                } else {
                    fmt::println(stderr, "Bad action: {}", pfs::to_string(action));
                    return EXIT_FAILURE;
                }
            } else {
                fmt::println(stderr, "Expected action");
                return EXIT_FAILURE;
            }
        }
    } else {
        print_usage(programName);
    }

    return EXIT_SUCCESS;
}
