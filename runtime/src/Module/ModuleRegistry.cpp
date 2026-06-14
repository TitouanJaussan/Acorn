#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    ModuleRegistry::ModuleRegistry(Core::LoggerFactory& factory)
        : m_logger(factory.create("ModRegistry")),
          m_modules{}
    {}

    void ModuleRegistry::registerModule(UniquePtr<RuntimeModule> mod)
    {
        m_logger.info(
            "Registered {} module {} ({})",
            mod->getManifest().name,
            mod->getManifest().runtimeVersion.string(),
            mod->getLibPath().filename().string()
        );

        m_modules.append(std::move(mod));
    }

    const ArrayList<UniquePtr<RuntimeModule>>& ModuleRegistry::getModules() const
    {
        return m_modules;
    }
}
