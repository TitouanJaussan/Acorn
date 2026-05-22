#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Module
{
    ModuleLoader::ModuleLoader(Core::LoggerFactory factory)
        : m_logger(factory.create("ModLoader"))
    {}

    void ModuleLoader::loadModules(
        std::filesystem::path folderPath,
        ModuleRegistry& registry)
    {
        for (const auto item: std::filesystem::directory_iterator(folderPath))
        {
            if (std::filesystem::is_directory(item))
            {
                loadModules(item, registry);
                continue;
            }

            loadModule(item, registry);
        }
    }

    void ModuleLoader::loadModule(std::filesystem::path modLibPath,
        ModuleRegistry& registry) noexcept
    {
        try
        {
            registry.registerMod(std::make_unique<Module>(
                ModuleDescriptor
                {
                    .libPath = modLibPath
                }
            ));
        }
        catch (const Core::DetailedError& err)
        {
            m_logger.error("{}", err.what());
        }
    }
}
