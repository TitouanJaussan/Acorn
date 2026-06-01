#pragma once

#include <utility>

#include "Acorn/Core/Memory/Mem.hpp"
#include "Acorn/Templates/UniquePtr.hpp"

namespace Acorn
{
    template<typename T>
    UniquePtr<T>::UniquePtr() noexcept
        : m_ptr(nullptr)
    {}

    template<typename T>
    UniquePtr<T>::UniquePtr(T* ptr) noexcept
        : m_ptr(ptr)
    {}

    template<typename T>
    UniquePtr<T>::UniquePtr(UniquePtr&& other)
        : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    template<typename T>
    UniquePtr<T>::UniquePtr(const UniquePtr& other)
        : m_ptr(mem_new<T>(other))
    {}

    template<typename T>
    UniquePtr<T>::~UniquePtr()
    {
        reset();
    }

    template<typename T>
    T* UniquePtr<T>::operator->() const noexcept
    {
        return m_ptr;
    }

    template<typename T>
    T& UniquePtr<T>::operator*() const noexcept
    {
        return *m_ptr;
    }

    template<typename T>
    UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other)
    {
        reset();

        m_ptr = other.m_ptr;
        other.reset();

        return *this;
    }

    template<typename T>
    UniquePtr<T>& UniquePtr<T>::operator=(const UniquePtr<T>& other)
    {
        reset();

        m_ptr = mem_new<T>(other);

        return *this;
    }

    template<typename T>
    T* UniquePtr<T>::getPtr() const noexcept
    {
        return m_ptr;
    }

    template<typename T>
    void UniquePtr<T>::reset()
    {
        if (!m_ptr)
            return;
    
        // m_ptr->~T();  // Why does calling this cause a segfault and jump to 0x0 ???

        mem_delete(m_ptr);

        m_ptr = nullptr;
    }

    template<typename T>
    template<typename... Args>
    UniquePtr<T> UniquePtr<T>::createUniquePtr(Args&&... args)
    {
        return UniquePtr<T>{mem_new<T>(std::forward<Args>(args)...)};
    }
}
