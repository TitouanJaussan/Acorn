#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Core/DetailedError.hpp"
#include "Acorn/Module/RuntimeModuleDescriptor.hpp"

namespace Acorn::Module
{
    ModuleLoader::ModuleLoader(Core::LoggerFactory& factory)
        : m_logger(factory.create("ModLoader"))
    {}

    void ModuleLoader::loadModules(
        std::filesystem::path folderPath,
        ModuleRegistry& registry,
        Core::LoggerFactory& factory,
        Core::RuntimeAPI runtime)
    {
        for (const auto& item: std::filesystem::directory_iterator(folderPath))
        {
            if (std::filesystem::is_directory(item))
            {
                loadModules(item, registry, factory, runtime);
                continue;
            }

            loadModule(item, registry, factory, runtime);
        }
    }

    void ModuleLoader::loadModule(std::filesystem::path modLibPath,
        ModuleRegistry& registry,
        Core::LoggerFactory& factory,
        Core::RuntimeAPI api) noexcept
    {
        try
        {
            // TODO: Somehow call destroyModule() in case the module doesn't load properly
            registry.registerModule(
                std::make_unique<RuntimeModule>(
                    RuntimeModuleDescriptor
                    {
                        .lib = Lib::DynamicLibrary{modLibPath},
                        .api = api,
                        .loggerFactory = factory
                    }
                )
            );
        }
        catch (const Core::DetailedError& err)
        {
            m_logger.error("Couldn't load module '{}': {}", modLibPath.filename().string(), err.what());
        }
    }
}
