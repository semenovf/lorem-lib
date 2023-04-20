////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/lorem_ipsum.hpp"
#include "pfs/lorem/utils.hpp"
#include "pfs/assert.hpp"
#include "pfs/fmt.hpp"
#include <array>
#include <string>
#include <system_error>

// Inspired by https://github.com/fzaninotto/Faker (original project) and
//             https://github.com/FakerPHP/Faker

namespace lorem {

static const std::string __orig_para[3] = {
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod"
      " tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim"
      " veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea"
      " commodo consequat."
    , "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum"
      " dolore eu fugiat nulla pariatur."
    , "Excepteur sint occaecat cupidatat non proident, sunt in"
      " culpa qui officia deserunt mollit anim id est laborum."
};

static const std::array<std::string, 249> __words = {
      "alias", "consequatur", "aut", "perferendis", "sit", "voluptatem"
    , "accusantium", "doloremque", "aperiam", "eaque","ipsa", "quae", "ab"
    , "illo", "inventore", "veritatis", "et", "quasi", "architecto"
    , "beatae", "vitae", "dicta", "sunt", "explicabo", "aspernatur", "aut"
    , "odit", "aut", "fugit", "sed", "quia", "consequuntur", "magni"
    , "dolores", "eos", "qui", "ratione", "voluptatem", "sequi", "nesciunt"
    , "neque", "dolorem", "ipsum", "quia", "dolor", "sit", "amet"
    , "consectetur", "adipisci", "velit", "sed", "quia", "non", "numquam"
    , "eius", "modi", "tempora", "incidunt", "ut", "labore", "et", "dolore"
    , "magnam", "aliquam", "quaerat", "voluptatem", "ut", "enim", "ad"
    , "minima", "veniam", "quis", "nostrum", "exercitationem", "ullam"
    , "corporis", "nemo", "enim", "ipsam", "voluptatem", "quia", "voluptas"
    , "sit", "suscipit", "laboriosam", "nisi", "ut", "aliquid", "ex", "ea"
    , "commodi", "consequatur", "quis", "autem", "vel", "eum", "iure"
    , "reprehenderit", "qui", "in", "ea", "voluptate", "velit", "esse"
    , "quam", "nihil", "molestiae", "et", "iusto", "odio", "dignissimos"
    , "ducimus", "qui", "blanditiis", "praesentium", "laudantium", "totam"
    , "rem", "voluptatum", "deleniti", "atque", "corrupti", "quos"
    , "dolores", "et", "quas", "molestias", "excepturi", "sint"
    , "occaecati", "cupiditate", "non", "provident", "sed", "ut"
    , "perspiciatis", "unde", "omnis", "iste", "natus", "error"
    , "similique", "sunt", "in", "culpa", "qui", "officia", "deserunt"
    , "mollitia", "animi", "id", "est", "laborum", "et", "dolorum", "fuga"
    , "et", "harum", "quidem", "rerum", "facilis", "est", "et", "expedita"
    , "distinctio", "nam", "libero", "tempore", "cum", "soluta", "nobis"
    , "est", "eligendi", "optio", "cumque", "nihil", "impedit", "quo"
    , "porro", "quisquam", "est", "qui", "minus", "id", "quod", "maxime"
    , "placeat", "facere", "possimus", "omnis", "voluptas", "assumenda"
    , "est", "omnis", "dolor", "repellendus", "temporibus", "autem"
    , "quibusdam", "et", "aut", "consequatur", "vel", "illum", "qui"
    , "dolorem", "eum", "fugiat", "quo", "voluptas", "nulla", "pariatur"
    , "at", "vero", "eos", "et", "accusamus", "officiis", "debitis", "aut"
    , "rerum", "necessitatibus", "saepe", "eveniet", "ut", "et"
    , "voluptates", "repudiandae", "sint", "et", "molestiae", "non"
    , "recusandae", "itaque", "earum", "rerum", "hic", "tenetur", "a"
    , "sapiente", "delectus", "ut", "aut", "reiciendis", "voluptatibus"
    , "maiores", "doloribus", "asperiores", "repellat"
};

inline void check_range (unsigned int from, unsigned int to)
{
    if (from == 0 || to == 0 || from > to)
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));
}

lorem_ipsum::lorem_ipsum ()
{}

void lorem_ipsum::set_word_range (unsigned int from, unsigned int to)
{
    check_range(from, to);
    _opts.word_range = std::make_pair(from, to);
}

void lorem_ipsum::set_sentence_range (unsigned int from, unsigned int to)
{
    check_range(from, to);
    _opts.sentence_range = std::make_pair(from, to);
}

void lorem_ipsum::set_paragraph_range (unsigned int from, unsigned int to)
{
    check_range(from, to);
    _opts.para_range = std::make_pair(from, to);
}

static std::string generate_sentence (unsigned int wc)
{
    PFS__TERMINATE(wc > 0, "");
    std::string result;
    result.reserve(wc * 8);

    std::string first_word = capitalize(__words[index(__words.size())]);
    result += first_word;
    --wc;

    while (wc--) {
        result += " ";
        result += __words[index(__words.size())];
    }

    result += ".";
    return result;
}

std::vector<paragraph_t>
lorem_ipsum::operator () () const
{
    auto pc = unsigned_integer(_opts.para_range.first
        , _opts.para_range.second);

    PFS__TERMINATE(pc > 0, "");

    std::vector<paragraph_t> paras;
    paras.reserve(pc);

    auto sc = unsigned_integer(_opts.sentence_range.first
        , _opts.sentence_range.second);

    PFS__TERMINATE(sc > 0, "");

    if (_opts.begin_with_orig_paragraph) {
        if (sc-- > 0) {
            pc--;
            paras.emplace_back();
            paras[0].push_back(__orig_para[0]);
        }

        if (sc-- > 0)
            paras[0].push_back(__orig_para[1]);

        if (sc-- > 0)
            paras[0].push_back(__orig_para[2]);

        while (sc-- > 0) {
            auto wc = unsigned_integer(_opts.word_range.first, _opts.word_range.second);
            paras[0].push_back(generate_sentence(wc));
        }
    }

    while (pc-- > 0) {
        paras.emplace_back();
        auto & para = paras.back();

        sc = unsigned_integer(_opts.sentence_range.first
            , _opts.sentence_range.second);

        while (sc-- > 0) {
            auto wc = unsigned_integer(_opts.word_range.first, _opts.word_range.second);
            para.push_back(generate_sentence(wc));
        }
    }

    return paras;
}

void lorem_ipsum::print (FILE * out) const
{
    auto paras = (*this)();
    char const * para_delim = "";

    for (auto const & para: paras) {
        fmt::print(out, para_delim);

        for (auto const & sentence: para) {
            fmt::print(out, sentence);
            fmt::print(out, "\n");
        }

        para_delim = "\n";
    }
}

} // namespace lorem
