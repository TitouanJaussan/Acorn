#ifndef ACORN_MEMORY_MEM_HPP
#define ACORN_MEMORY_MEM_HPP

#include <cstddef>

#include "Acorn/EngineAPI.hpp"

// Should all this go into Acorn::Memory namespace ??
template<typename T, typename... Args>
ENGINE_API T* mem_new(Args&&... args);
template<typename T>
ENGINE_API void mem_delete(T* ptr);

ENGINE_API void* op_new(size_t size);
ENGINE_API void  op_delete(void* ptr, size_t size);

#include "Acorn/Base/Memory/Mem.ipp"

#endif /* ACORN_MEMORY_MEM_HPP */
