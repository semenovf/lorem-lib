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
#include "pfs/lorem/lang_domain.hpp"
#include "pfs/lorem/lorem_ipsum.hpp"
#include "pfs/lorem/person.hpp"
#include "pfs/lorem/utils.hpp"
#include "docopt.h"
#include <stdexcept>
#include <string>

//#include <iostream>

static char const * TAG = "LOREM";

static struct program_context {
    std::string program;
} __pctx;

std::string const USAGE =
R"(Usage:
    lorem_ipsum ipsum [--para-count=<pc> | -P <pc>]
        [--sentence-count=<sc> | -S <sc> ]
        [--word-count=<wc> | -W <wc>] [-O]
    lorem_ipsum person [--lang-domain=<ld> | -D <ld>] [--gender=<gender> | -G <gender>]
        [--count=NUMBER] [--format=FORMAT | --full-name=TYPE]
    lorem_ipsum (-h | --help)

Options:
    -h --help
        Show this screen.

IPSUM options:

    --para-count=<para-count> | -P <para-count>
        Number of paragraphs.

    --sentence-count=NUMBER
        Number of sentences in a paragraph.

    --word-count=NUMBER
        Number of words in a sentence.

    -O
        Begin with original Lorem ipsum paragraph.

PERSON options:

    --lang-domain=<ld> | -D <ld>
        Language domain (ru_RU, en_US, etc).

    --gender=<gender> | -G <gender>
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

void ipsum_action (docopt::Options const & args)
{
    lorem::lorem_ipsum ipsum;

    try {
        if (args.at("-P").asBool())
            ipsum.set_paragraph_count(static_cast<unsigned int>(args.at("<pc>").asLong()));

        if (args.at("--para-count"))
            ipsum.set_paragraph_count(static_cast<unsigned int>(args.at("--para-count").asLong()));

        if (args.at("-S").asBool())
            ipsum.set_sentence_count(static_cast<unsigned int>(args.at("<sc>").asLong()));

        if (args.at("--sentence-count"))
            ipsum.set_sentence_count(static_cast<unsigned int>(args.at("--sentence-count").asLong()));

        if (args.at("-W").asBool())
            ipsum.set_word_count(static_cast<unsigned int>(args.at("<wc>").asLong()));

        if (args.at("--word-count"))
            ipsum.set_word_count(static_cast<unsigned int>(args.at("--word-count").asLong()));

        if (args.at("-O").asBool())
            ipsum.begin_with_orig_paragraph(true);

    } catch (std::runtime_error const & ex) {
        LOGEXP(TAG, ex);
        return;
    } catch (std::invalid_argument const & /*ex*/) {
        LOGE(TAG, "invalid argument: {}");
        return;
    }

    ipsum.print();
}

void person_action (docopt::Options const & args)
{
    pfs::optional<lorem::lang_domain> ld {lorem::lang_domain::en_US};
    auto gender = lorem::gender::male;
    int count = 1;
    std::string full_name;
    std::string format;

//     for (auto a: args) {
//         std::cout << a.first << ": " << a.second << "\n";
//     }

    try {
        std::string optname = "-D";

        if (args.at(optname).asBool()) {
            ld = lorem::lang_domain_from_string(args.at("<ld>").asString());

            if (!ld)
                throw std::invalid_argument{"-D"};
        }

        optname = "--lang-domain";

        if (args.at(optname)) {
            ld = lorem::lang_domain_from_string(args.at(optname).asString());

            if (!ld)
                throw std::invalid_argument{optname};
        }

        std::string gender_str = "m";

        if (args.at("-G").asBool())
            gender_str = args.at("<gender>").asString();

        optname = "--gender";

        if (args.at(optname))
            gender_str = args.at(optname).asString();

        if (gender_str == "m") {
            gender = lorem::gender::male;
        } else if (gender_str == "f") {
            gender = lorem::gender::female;
        } else {
            throw std::invalid_argument{"--gender or -G"};
        }

        optname = "--count";

        if (args.at(optname)) {
            count = static_cast<int>(args.at(optname).asLong());

            if (count < 0) {
                throw std::invalid_argument{optname};
            }
        }

        optname = "--format";

        if (args.at(optname))
            format = args.at(optname).asString();

        optname = "--full-name";

        if (args.at(optname)) {
            full_name = args.at(optname).asString();

            if (!(full_name == "last" || full_name == "first"))
                throw std::invalid_argument{optname};
        }

    } catch (std::runtime_error const & ex) {
        LOGEXP(TAG, ex);
        return;
    } catch (std::invalid_argument const & ex) {
        LOGE(TAG, "invalid argument: {}", ex.what());
        return;
    }

    lorem::person person {*ld, gender};

    while (count-- > 0) {
        if (!format.empty()) {
            fmt::print("{}\n", person.format(format));
        } else {
            if ((!full_name.empty())) {
                if (full_name == "last")
                    fmt::print("{}\n", person.full_name(true));
                else
                    fmt::print("{}\n", person.full_name(false));
            } else {
                fmt::print("{}\n", person.full_name());
            }
        }
    }
}

int main (int argc, char * argv[])
{
    __pctx.program = argv[0];

    bool stopOnHelp    = true;  // end early if '-h' or '--help' is in the argv
    bool stopOnVersion = true;  // end early if '--version' is in the argv
    bool optionsFirst  = false; // args and options can be arbitrarily mixed

    docopt::Options args;

    try {
        args = docopt::docopt_parse(USAGE
            , { argv + 1, argv + argc }, stopOnHelp, stopOnVersion, optionsFirst);
    } catch (docopt::DocoptExitHelp const &) {
        fmt::print(USAGE);
        return EXIT_SUCCESS;
    } catch (docopt::DocoptLanguageError const & error) {
        LOGE(TAG, "Docopt usage string could not be parsed: {}\n", error.what());
        return EXIT_FAILURE;
    } catch (docopt::DocoptArgumentError const & error) {
        LOGE(TAG, "Argument error: {}\n", error.what());
        return EXIT_FAILURE;
    }

    if (args.at("ipsum").asBool()) {
        ipsum_action(args);
    } else if (args.at("person").asBool()) {
        person_action(args);
    }

    return EXIT_SUCCESS;
}
