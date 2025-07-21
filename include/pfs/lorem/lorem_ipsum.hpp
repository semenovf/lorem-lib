////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "exports.hpp"
#include "namespace.hpp"
#include <cstdio>
#include <string>
#include <vector>

LOREM__NAMESPACE_BEGIN

using sentence_t = std::string;
using paragraph_t = std::vector<sentence_t>;

class lorem_ipsum
{
    struct opts
    {
        bool begin_with_orig_paragraph {false};

        // Range of the words in sentence.
        std::pair<unsigned int, unsigned int> word_range {1,1};

        // Range of the paragraphs
        std::pair<unsigned int, unsigned int> para_range {1,1};

        // Range of the sentences in the paragraph
        std::pair<unsigned int, unsigned int> sentence_range {1,1};
    } _opts;

public:
    // Generates original paragraph by default
    LOREM__EXPORT lorem_ipsum ();

    void begin_with_orig_paragraph (bool on)
    {
        _opts.begin_with_orig_paragraph = on;
    }

    LOREM__EXPORT void set_word_range (unsigned int from, unsigned int to);

    inline void set_word_count (unsigned int n)
    {
        set_word_range(n, n);
    }

    LOREM__EXPORT void set_sentence_range (unsigned int from, unsigned int to);

    void set_sentence_count (unsigned int n)
    {
        set_sentence_range(n, n);
    }

    LOREM__EXPORT void set_paragraph_range (unsigned int from, unsigned int to);

    void set_paragraph_count (unsigned int n)
    {
        set_paragraph_range(n, n);
    }

    /**
     * Returns generated paragraphs.
     */
    LOREM__EXPORT std::vector<paragraph_t> operator () () const;

    /**
     * Print paragraphs into specified stream.
     */
    LOREM__EXPORT void print (FILE * out = stdout) const;
};

LOREM__NAMESPACE_END
