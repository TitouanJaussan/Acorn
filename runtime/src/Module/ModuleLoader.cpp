#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Core/DetailedError.hpp"
#include "Acorn/Module/ModuleError.hpp"
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
            UniquePtr<RuntimeModule> mod = UniquePtr<RuntimeModule>::createUniquePtr(
                RuntimeModuleDescriptor
                {
                    .lib = Lib::DynamicLibrary{modLibPath},
                    .api = api,
                    .loggerFactory = factory
                }
            );

            validateModuleCompatibility(mod->getManifest(), api);

            registry.registerModule(std::move(mod));
        }
        catch (const Core::DetailedError& err)
        {
            m_logger.error("Couldn't load module '{}': {}",
                modLibPath.filename().string(),
                err.what()
            );
        }
    }

    void ModuleLoader::validateModuleCompatibility(const ModuleManifest& manifest,
        const Core::RuntimeAPI& api)
    {
        if (api.version().major() > manifest.runtimeVersion.major())
        {
            throw ModuleError(std::format(
                "Module version too old ({}) for runtime ({})",
                manifest.runtimeVersion.string(),
                api.version().string()
            ).c_str());
        }
        else if (api.version().minor() > manifest.runtimeVersion.minor())
        {
            m_logger.warn(
                "Module version ({}) older than runtime version ({}), possible incompatibility",
                manifest.runtimeVersion.string(),
                api.version().string()
            );
        }
    }
}
