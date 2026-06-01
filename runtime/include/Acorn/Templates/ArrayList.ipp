#pragma once

#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "Acorn/Core/Memory/Mem.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Core/Assert.hpp"

namespace Acorn
{
    template<typename T>
    ArrayList<T>::ArrayList() noexcept
        : m_arr(nullptr),
          m_size(0),
          m_capacity(0)
    {}
    
    template<typename T>
    ArrayList<T>::ArrayList(const ArrayList& other)
        : m_arr(nullptr),
          m_size(0),
          m_capacity(0)
    {
        ACORN_ASSERT(other.m_arr != nullptr);

        setCapacity(other.m_capacity);
        m_size = other.m_size;

        size_t i = 0;
        for (const auto& val: other)
            new (&m_arr[i++]) T(val);
    }

    template<typename T>
    ArrayList<T>::ArrayList(ArrayList&& other)
        : m_arr(other.m_arr),
          m_size(other.m_size),
          m_capacity(other.m_capacity)
    {
        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    template<typename T>
    ArrayList<T>::ArrayList(std::initializer_list<T> list)
        : m_arr(nullptr),
          m_size(0),
          m_capacity(0)
    {
        setCapacity(list.size());

        for (const auto& v: list)
            append(v);
    }

    template<typename T>
    ArrayList<T>::~ArrayList()
    {
        destroyInternalArray();
    }

    template<typename T>
    T& ArrayList<T>::operator[](size_t i) noexcept
    {
        ACORN_ASSERT(i < m_capacity);
        return m_arr[i];
    }

    template<typename T>
    const T& ArrayList<T>::operator[](size_t i) const noexcept
    {
        ACORN_ASSERT(i < m_capacity);
        return m_arr[i];
    }

    template<typename T>
    ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other)
    {
        destroyInternalArray();

        m_arr = other.m_arr;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    template<typename T>
    ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other)
    {
        if (this == &other)
            return *this;

        destroyInternalArray();

        m_size = other.m_size;
        m_capacity = 0;
        setCapacity(other.m_capacity);

        size_t i = 0;
        for (auto& val: other)
            new (&m_arr[i++]) T(val);

        return *this;
    }

    template<typename T>
    void ArrayList<T>::append(const T& val)
    {
        if (m_size == m_capacity)
            growCapacity();

        new (&m_arr[m_size++]) T(val);
    }

    template<typename T>
    void ArrayList<T>::append(T&& val)
    {
        if (m_size == m_capacity)
            growCapacity();

        new (&m_arr[m_size++]) T(std::move(val));
    }

    template<typename T>
    template<typename... Args>
    void ArrayList<T>::emplace(Args&&... args)
    {
        if (m_size == m_capacity)
            growCapacity();

        new (&m_arr[m_size++]) T(std::forward<Args>(args)...);
    }

    template<typename T>
    void ArrayList<T>::insert(size_t index, T val)
    {
        ACORN_ASSERT(m_size > 0);
        ACORN_ASSERT(index < m_size);

        if (m_size == m_capacity)
            growCapacity();

        // I guess all this handles overlapping memory regions (it does)
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            memmove(m_arr + index + 1,
                    m_arr + index,
                    (m_size - index) * sizeof(T));

            m_arr[index] = val;
        }
        else
        {
            for (ptrdiff_t i = m_size - 1;
                 i >= static_cast<ptrdiff_t>(index);
                 --i)
            {
                new (m_arr + i + 1) T(std::move(m_arr[i]));

                if constexpr (!std::is_trivially_destructible_v<T>)
                    m_arr[i].~T();
            }

            new (m_arr + index) T(std::move(val));
        }

        ++m_size;
    }

    template<typename T>
    void ArrayList<T>::insert(size_t pos, Iterator first, Iterator last)
    {
        const size_t dist = static_cast<size_t>(std::distance(first, last));

        while (m_size + dist > m_capacity)
            growCapacity();

        if constexpr (std::is_trivially_copyable_v<T>)
        {
            memmove(m_arr + pos + dist,
                    m_arr + pos,
                    (m_size - pos) * sizeof(T));

            memcpy(m_arr + pos, &(*first), dist * sizeof(T));
        }
        else
        {
            for (ptrdiff_t i = m_size - 1;
                 i >= static_cast<ptrdiff_t>(pos);
                 --i)
            {
                new (m_arr + i + dist) T(std::move(m_arr[i]));

                if constexpr (!std::is_trivially_destructible_v<T>)
                    m_arr[i].~T();
            }

            size_t i = pos;
            for (auto it = first; it != last; ++it)
                new (&m_arr[i++]) T(std::move(*it));
        }

        m_size += dist;
    }

    template<typename T>
    size_t ArrayList<T>::getCapacity() const noexcept
    {
        return m_capacity;
    }

    template<typename T>
    size_t ArrayList<T>::getSize() const noexcept
    {
        return m_size;
    }

    template<typename T>
    T* ArrayList<T>::getData() const noexcept
    {
        return m_arr;
    }

    template<typename T>
    bool ArrayList<T>::isEmpty() const noexcept
    {
        return m_size == 0;
    }

    template<typename T>
    void ArrayList<T>::setCapacity(size_t newCapacity)
    {
        ACORN_ASSERT(newCapacity != 0 && "Can't set ArrayList capacity to 0");
        ACORN_ASSERT(newCapacity >= m_size && "Can't shrink ArrayList capacity below it's size");

        T* newArr = static_cast<T*>(op_new(newCapacity * sizeof(T)));

        if constexpr (std::is_trivially_copyable_v<T>)
        {
            if (m_arr)
                memcpy(newArr, m_arr, m_size * sizeof(T));
        }
        else
        {
            for (ptrdiff_t i = m_size - 1; i >= 0; --i)
            {
                new (newArr + i) T(std::move(m_arr[i]));
                
                // if constexpr (!std::is_trivially_destructible_v<T>)
                    // m_arr[i].~T();
            }
        }

        destroyInternalArray();

        m_arr = newArr;
        m_capacity = newCapacity;
    }

    template<typename T>
    void ArrayList<T>::clearAll()
    {
        destructAll();
    }

    template<typename T>
    void ArrayList<T>::growCapacity()
    {
        if (m_capacity == 0)
            setCapacity(1);
        else
            setCapacity(m_capacity * 2);
    }

    template<typename T>
    void ArrayList<T>::destructAll()
    {
        if (!m_arr) return;

        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (ptrdiff_t i = m_size - 1; i >= 0; --i)
                m_arr[i].~T();
        }

        m_size = 0;
    }

    template<typename T>
    void ArrayList<T>::destroyInternalArray()
    {
        destructAll();
        op_delete(m_arr, m_capacity * sizeof(T));
    }
}
