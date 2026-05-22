#include "Acorn/DynamicLib/DynamicLibrary.hpp"
#include "Acorn/Core/DetailedError.hpp"

#include <filesystem>
#include <format>

namespace Acorn::Lib
{
    DynamicLibrary::DynamicLibrary(std::filesystem::path libPath)
        : path(libPath),
          m_handle(LOAD_LIB(libPath.c_str()))
    {
        if (!m_handle)
        {
            // TODO: Custom error type 
            throw Core::DetailedError(
                "Dynamic Library",
                std::format(
                    "Failed to load dynamic library '{}', cause: '{}'",
                    libPath.string(),
                    LIB_GET_ERR()
                )
            );
        }
    }

    DynamicLibrary::DynamicLibrary(DynamicLibrary&& other)
        : path(other.path),
          m_handle(other.m_handle)
    {
        other.path.string().clear();
        other.m_handle = nullptr;
    }

    DynamicLibrary::~DynamicLibrary()
    {
        CLOSE_LIB(m_handle);
        m_handle = nullptr;
    }

    void* DynamicLibrary::resolveSymbol(const char* symbolName) const
    {
        return LIB_RESOLVE_SYMBOL(m_handle, symbolName);
    }
}
