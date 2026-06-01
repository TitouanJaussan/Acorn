#include "Acorn/Core/Memory/Mem.hpp"
#include "Acorn/Core/Memory/Tracker.hpp"

#define TRACKER Acorn::Memory::Tracker::getSingleton()

void* op_new(size_t size)
{
    void* ptr = ::operator new(size);

    TRACKER->recordAlloc(size);

    return ptr;
}

void op_delete(void* ptr, size_t size)
{
    ::operator delete(ptr);

    TRACKER->recordDealloc(size);
}
