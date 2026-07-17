#pragma once

#include <cmath>

#include "Acorn/Base/Math/Vec.hpp"

namespace Acorn::Math
{
    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T>::Vec(T scalar) noexcept
        : m_vec(scalar)
    {}

    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T>::Vec(T x, T y) noexcept 
    requires (componentsCount == 2)
        : m_vec(x, y)
    {}

    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T>::Vec(T x, T y, T z) noexcept 
    requires (componentsCount == 3)
        : m_vec(x, y, z)
    {}

    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T>::Vec(T x, T y, T z, T w) noexcept 
    requires (componentsCount == 4)
        : m_vec(x, y, z, w)
    {}

    template<size_t componentsCount, VecType T>
    T& Vec<componentsCount, T>::x() noexcept
    {
        return m_vec.x;
    }

    template<size_t componentsCount, VecType T>
    T& Vec<componentsCount, T>::y() noexcept
    {
        return m_vec.y;
    }

    template<size_t componentsCount, VecType T>
    T& Vec<componentsCount, T>::z() noexcept
    requires (componentsCount > 2)
    {
        return m_vec.z;
    }

    template<size_t componentsCount, VecType T>
    T& Vec<componentsCount, T>::w() noexcept
    requires (componentsCount > 3)
    {
        return m_vec.w;
    }

    template<size_t componentsCount, VecType T>
    T Vec<componentsCount, T>::x() const noexcept
    {
        return m_vec.x;
    }

    template<size_t componentsCount, VecType T>
    T Vec<componentsCount, T>::y() const noexcept
    {
        return m_vec.y;
    }

    template<size_t componentsCount, VecType T>
    T Vec<componentsCount, T>::z() const noexcept
    requires (componentsCount > 2)
    {
        return m_vec.z;
    }

    template<size_t componentsCount, VecType T>
    T Vec<componentsCount, T>::w() const noexcept
    requires (componentsCount > 3)
    {
        return m_vec.w;
    }

    template<size_t componentsCount, VecType T>
    float Vec<componentsCount, T>::length() const noexcept
    {
        return sqrt(m_vec.x * m_vec.x + m_vec.y * m_vec.y);
    }

    template<size_t componentsCount, VecType T>
    float Vec<componentsCount, T>::lengthSqrd() const noexcept
    {
        return m_vec.x * m_vec.x + m_vec.y * m_vec.y;
    }

    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T> Vec<componentsCount, T>::ZERO() noexcept
    {
        return Vec(0.0f);
    }

    template<size_t componentsCount, VecType T>
    Vec<componentsCount, T> Vec<componentsCount, T>::ONE() noexcept
    {
        return Vec(1.0f);
    }
}
