////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "pfs/lorem/person.hpp"
#include "person_impl.hpp"
#include <stdexcept>

namespace lorem {

extern "C" lorem::person::impl const * person_en_US (lorem::gender g);
extern "C" lorem::person::impl const * person_ru_RU (lorem::gender g);

person::person (lang_domain ld, gender g)
{
    switch (ld) {
        case lang_domain::ru_RU:
            _d = person_ru_RU(g);
            break;

        case lang_domain::en_US:
            _d = person_en_US(g);
        default:
            break;
    }

    if (!_d)
        throw std::invalid_argument{"unsupported language domain"};
}

std::string person::first_name (int index) const
{
    return _d->first_name(index);
}

std::string person::middle_name (int index) const
{
    return _d->middle_name(index);
}

std::string person::last_name (int index) const
{
    return _d->last_name(index);
}

std::string person::full_name (bool last_is_first) const
{
    return _d->full_name(last_is_first);
}

std::string person::full_name () const
{
    return _d->full_name();
}

std::string person::format (int index, std::string const & fm) const
{
    std::string result;
    auto spec_char = false;

    for (char ch: fm) {
        if (spec_char) {
            switch (ch) {
                case 'f':
                    result += first_name(index);
                    break;
                case 'l':
                    result += last_name(index);
                    break;
                case 'm':
                    result += middle_name(index);
                    break;
                case '%':
                    result += '%';
                    break;
                default:
                    throw std::invalid_argument{"lorem::person::format"};
            }

            spec_char = false;
        } else {
            if (ch == '%')
                spec_char = true;
            else
                result += ch;
        }
    }

    if (spec_char)
        throw std::invalid_argument{"lorem::person::format"};

    return result;
}

} // namespace lorem

