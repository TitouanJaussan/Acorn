#pragma once

#include "Acorn/DynamicLib/DynamicLibrary.hpp"
#include "Acorn/DynamicLib/DynamicLibraryError.hpp"
#include "Acorn/Base/Format.hpp"

namespace Acorn::Lib
{
    template<typename T>
    T DynamicLibrary::resolveSymbol(const char* name) const
    {
        if (!m_handle)
        {
            throw DynamicLibraryError(
                Base::format("Can't resolve symbol, handle is NULL")
            );
        }

        const void* sym = LIB_RESOLVE_SYMBOL(m_handle, name);

        if (!sym)
            throw DynamicLibraryError(
                Base::format(
                    "Can't resolve '{}', no such symbol found",
                    name
                ).getData()
            );

        return (T)sym;
    }
}
