#ifndef ACORN_MODULE_HPP
#define ACORN_MODULE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Module/ModuleDescriptor.hpp"
#include "Acorn/DynamicLib/DynamicLibrary.hpp"

namespace Acorn::Module
{
    class ENGINE_API Module
    {
        Lib::DynamicLibrary m_lib;

    public:
        Module(ModuleDescriptor descriptor);

        std::filesystem::path libPath() const noexcept;

        const char* const name;

        const void(*load)();
        const void(*update)();
        const void(*render)();
        const void(*unload)();
    };
}

#endif /* ACORN_MODULE_HPP */
