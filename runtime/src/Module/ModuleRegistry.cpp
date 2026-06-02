#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    ModuleRegistry::ModuleRegistry(Core::LoggerFactory& factory)
        : m_modules{},
          m_logger(factory.create("ModRegistry"))
    {}

    void ModuleRegistry::registerModule(UniquePtr<RuntimeModule> mod)
    {
        m_logger.info(
            "Registered {} module ({})",
            mod->getManifest().name,
            mod->getLibPath().filename().string()
        );

        m_modules.append(std::move(mod));
    }

    const ArrayList<UniquePtr<RuntimeModule>>& ModuleRegistry::getModules() const
    {
        return m_modules;
    }
}
