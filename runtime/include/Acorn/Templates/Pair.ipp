#pragma once

#include <utility>

#include "Acorn/Templates/Pair.hpp"

namespace Acorn
{
    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(T1 first, T2 second)
        : m_first(std::move(first)),
          m_second(std::move(second))
    {}

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(Pair&& other)
        : m_first(std::move(other.m_first)),
          m_second(std::move(other.m_second))
    {}

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(const Pair& other)
        : m_first(other.m_first),
          m_second(other.m_second)
    {}
}
