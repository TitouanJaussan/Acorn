#ifndef ACORN_STRING_OUTPUT_ITERATOR_HPP
#define ACORN_STRING_OUTPUT_ITERATOR_HPP

#include <iterator>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn
{
    struct ENGINE_API StringOutputIterator
    {
        using iterator_category = std::output_iterator_tag;
        using value_type = void;
        using difference_type = std::ptrdiff_t;
        using pointer = void;
        using reference = void;

        String* str;

        StringOutputIterator& operator=(char c);
        StringOutputIterator& operator*();
        StringOutputIterator& operator++();
        StringOutputIterator& operator++(int);
    };
}

#endif /* ACORN_STRING_OUTPUT_ITERATOR_HPP */
