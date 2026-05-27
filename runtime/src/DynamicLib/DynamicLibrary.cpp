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

    DynamicLibrary::DynamicLibrary(DynamicLibrary&& other) noexcept
        : path(other.path),
          m_handle(other.m_handle)
    {
        other.m_handle = nullptr;
    }

    DynamicLibrary::~DynamicLibrary()
    {
        if (!m_handle) return;

        CLOSE_LIB(m_handle);
        m_handle = nullptr;
    }
}
