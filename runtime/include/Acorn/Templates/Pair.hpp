#ifndef ACORN_PAIR_HPP
#define ACORN_PAIR_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn
{
    template<typename T1, typename T2>
    class ENGINE_API Pair
    {
    public:
        Pair(T1 first, T2 second);
        Pair(Pair&& other);
        Pair(const Pair& other);

        T1 m_first;
        T2 m_second;
    };
}

#include "Acorn/Templates/Pair.ipp"

#endif /* ACORN_PAIR_HPP */
