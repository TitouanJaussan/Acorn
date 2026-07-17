#ifndef ACORN_MODULE_MANAGER_HANDLE_HPP
#define ACORN_MODULE_MANAGER_HANDLE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/String.hpp"
#include "Acorn/Module/APIHandle.hpp"

namespace Acorn::Module
{
    class ModuleManager;

    class ENGINE_API ModuleManagerHandle final
    {
    public:
        ModuleManagerHandle(ModuleManager& handle);

        APIHandle<> getModuleAPIHandle(String modName) const;

    private:
        ModuleManager& m_handle;
    };
}

#endif /* ACORN_MODULE_MANAGER_HANDLE_HPP */
