#pragma once

#include <format>

#include "Acorn/DynamicLib/DynamicLibrary.hpp"
#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Lib
{
    template<typename T>
    T DynamicLibrary::resolveSymbol(const char* name) const
    {
        if (!m_handle)
        {
            throw Core::DetailedError(
                "Dynamic Library",
                std::format("Can't resolve symbol, handle is NULL")
            );
        }

        const void* sym = LIB_RESOLVE_SYMBOL(m_handle, name);

        if (!sym)
            throw Core::DetailedError(
                "Dynamic Library",
                std::format("Can't resolve '{}', no such symbol found", name).c_str()
            );

        return (T)sym;
    }
}
