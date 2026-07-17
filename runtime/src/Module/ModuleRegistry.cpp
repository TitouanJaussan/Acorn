#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Base/Format.hpp"
#include "Acorn/Module/ModuleError.hpp"

namespace Acorn::Module
{
    ModuleRegistry::ModuleRegistry(Base::LoggerFactory& factory)
        : m_logger(factory.create("ModRegistry")),
          m_modules{},
          m_modsAPIs{}
    {}

    void ModuleRegistry::registerModule(UniquePtr<RuntimeModule> mod)
    {
        m_logger.info(
            "Registered {} module {} ({})",
            mod->getManifest().name,
            mod->getManifest().runtimeVersion.string(),
            mod->getLibPath().filename().string()
        );

        m_modsAPIs.append(UniquePtr<ModuleAPI>::create(nullptr));
        m_modules.append(std::move(mod));
    }

    const ArrayList<UniquePtr<RuntimeModule>>&
        ModuleRegistry::getModules() const
    {
        return m_modules;
    }

    RuntimeModule* ModuleRegistry::getModule(String name) const
    {
        for (const auto& mod: m_modules)
        {
            if (mod->getManifest().name == name)
                return mod.getPtr();
        }

        return nullptr;
    }

    APIHandle<> ModuleRegistry::getAPIHandle(String modName) const
    {
        ACORN_ASSERT(m_modules.getSize() == m_modsAPIs.getSize());

        const auto [found, index] = findModuleIndex(std::move(modName));

        if (!found)
            throw ModuleError(Base::format(
                "Module API not found for module '{}'", modName
            ));

        return APIHandle(m_modsAPIs[index].getPtr());
    }

    void ModuleRegistry::updateModuleAPI(String modName, void* newApiPtr)
    {
        const auto [found, index] = findModuleIndex(modName);

        if (!found)
        {
            m_logger.warn(
                "Can't update module api for unexisting module '{}'",
                modName);
            return;
        }

        m_modsAPIs[index]->modAPI = newApiPtr;
    }

    Pair<bool, size_t> ModuleRegistry::findModuleIndex(String modName) const
    {
        for (size_t i = 0; i < m_modules.getSize(); ++i)
        {
            if (m_modules[i]->getManifest().name == modName)
                return {true, i};
        }

        return {false, 0};
    }
}
