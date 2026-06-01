#pragma once

#include <utility>

#include "Acorn/Core/Memory/Mem.hpp"
#include "Acorn/Core/Memory/Tracker.hpp"

#define TRACKER Acorn::Memory::Tracker::getSingleton()

template<typename T, typename... Args>
T* mem_new(Args&&... args)
{
    T* ptr = new T{std::forward<Args>(args)...};

    TRACKER->recordAlloc(sizeof(T));

    return ptr;
}

template<typename T>
void mem_delete(T* ptr)
{
    delete ptr;

    TRACKER->recordDealloc(sizeof(T));
}

