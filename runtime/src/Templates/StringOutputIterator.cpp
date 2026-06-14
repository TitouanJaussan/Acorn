#include "Acorn/Templates/StringOutputIterator.hpp"

namespace Acorn
{
    StringOutputIterator& StringOutputIterator::operator=(char c)
    {
        str->append(c);
        return *this;
    }

    StringOutputIterator& StringOutputIterator::operator*()
    {
        return *this;
    }

    StringOutputIterator& StringOutputIterator::operator++()
    {
        return *this;
    }

    StringOutputIterator& StringOutputIterator::operator++(int)
    {
        return *this;
    }
}
