#ifndef ACORN_DYNAMIC_LIBRARY_HPP
#define ACORN_DYNAMIC_LIBRARY_HPP

#include <filesystem>

#ifdef _WIN32
    #include <windows.h>
    #define LIB_HANDLE HINSTANCE
    #define LOAD_LIB(name) LoadLibrary(name)
    #define CLOSE_LIB(lib)
    #define LIB_RESOLVE_SYMBOL(lib, symbolName) GetProcAddress(lib, name)
#else
    #include <dlfcn.h>
    #define LIB_HANDLE void*
    #define LOAD_LIB(name) dlopen(name, RTLD_NOW)
    #define CLOSE_LIB(lib) dlclose(lib)
    #define LIB_RESOLVE_SYMBOL(lib, symbolName) dlsym(lib, symbolName)
#endif /* _WIN32 */

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Lib
{
    class ENGINE_API DynamicLibrary
    {
    public:
        DynamicLibrary(std::filesystem::path libPath);
        DynamicLibrary(DynamicLibrary&& other);
        ~DynamicLibrary();

        void* resolveSymbol(const char* symbolName) const;

        const std::filesystem::path path;

    private:
        LIB_HANDLE m_handle;
    };
}

#endif /* ACORN_DYNAMIC_LIBRARY_HPP */
