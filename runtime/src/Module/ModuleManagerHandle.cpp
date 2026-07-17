#include "Acorn/Module/ModuleManagerHandle.hpp"
#include "Acorn/Module/ModuleManager.hpp"

namespace Acorn::Module
{
    ModuleManagerHandle::ModuleManagerHandle(ModuleManager& handle)
        : m_handle(handle)
    {}

    APIHandle<> ModuleManagerHandle::getModuleAPIHandle(String modName) const
    {
        return m_handle.modRegistry.getAPIHandle(std::move(modName));
    }
}
