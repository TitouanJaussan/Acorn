#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Core/DetailedError.hpp"
#include "Acorn/Module/ModuleError.hpp"
#include "Acorn/Module/RuntimeModuleDescriptor.hpp"

namespace Acorn::Module
{
    ModuleLoader::ModuleLoader(Core::LoggerFactory& factory)
        : m_logger(factory.create("ModLoader"))
    {}

    void ModuleLoader::loadModules(std::filesystem::path modsDirPath, ModLoadingCtx ctx)
    {
        ArrayList<std::filesystem::path> modsPaths = discoverMods(modsDirPath, ctx);
        ArrayList<UniquePtr<RuntimeModule>> mods{};

        for (const auto& modPath: modsPaths)
        {
            auto mod = loadModule(modPath, ctx);
            if (!mod) continue;

            mods.append(std::move(mod));
        }

        for (size_t i = 0; i < mods.getSize(); ++i)
            solveDependencies(mods, i);

        for (auto& mod: mods)
            ctx.modRegistry.registerModule(std::move(mod));
    }

    void ModuleLoader::solveDependencies(
        ArrayList<UniquePtr<RuntimeModule>>& mods,
        size_t modIndex)
    {
        while (modIndex < mods.getSize())
        {
            size_t totalSolvedDeps = 0;

            for (size_t depIdx = 0;
                 depIdx < mods[modIndex]->getManifest().dependencies.getSize();
                 ++depIdx)
            {
                size_t foundIdx = mods.findIndex(
                    [](UniquePtr<RuntimeModule>& mod, auto& mods, auto currModIndex, auto depIdx) -> bool
                    {
                        return mod->getManifest().name == mods[currModIndex]->getManifest().dependencies[depIdx];
                    }, mods, modIndex, depIdx
                );

                if (foundIdx == mods.getSize())
                {
                    // Dependency not here, let's not load this mod
                    m_logger.error(
                        "Could not solve dependencies for the {} module, loading aborted.",
                        mods[modIndex]->getManifest().name
                    );

                    mods.swap(modIndex, mods.getSize() - 1);
                    mods.popBack();
                    break;
                }

                // Now check order
                if (foundIdx > modIndex)
                {
                    mods.swap(modIndex, foundIdx);
                    depIdx = 0;
                    ++totalSolvedDeps;
                }
            }

            if (totalSolvedDeps == 0)
                break;  // Or return;
        }
    }

    ArrayList<std::filesystem::path> ModuleLoader::discoverMods(
        std::filesystem::path modsDirPath,
        ModLoadingCtx ctx)
    {
        ArrayList<std::filesystem::path> modPaths;

        for (const auto& item: std::filesystem::directory_iterator(modsDirPath))
        {
            if (std::filesystem::is_directory(item))
            {
                const auto other = discoverMods(modsDirPath, ctx);

                modPaths.insert(
                    modPaths.getSize(),
                    other.begin(),
                    other.end());

                continue;
            }

#ifdef _WIN32
            if (item.path().extension() != ".dll")
                continue;
#else
            if (item.path().extension() != ".so")
                continue;
#endif
            modPaths.append(item.path());
        }

        return modPaths;
    }

    UniquePtr<RuntimeModule> ModuleLoader::loadModule(
        std::filesystem::path modPath,
        ModLoadingCtx ctx) noexcept
    {
        try
        {
            UniquePtr<RuntimeModule> mod = UniquePtr<RuntimeModule>::create(
                RuntimeModuleDescriptor
                {
                    .lib = Lib::DynamicLibrary{modPath},
                    .api = ctx.runtimeAPI,
                    .loggerFactory = ctx.loggerFactory
                }
            );

            validateModuleCompatibility(mod->getManifest(), ctx.runtimeAPI);

            return mod;
        }
        catch (const Core::DetailedError& err)
        {
            m_logger.error("Couldn't load module '{}': {}",
                modPath.filename().string(),
                err.what()
            );
        }

        return {};
    }

    void ModuleLoader::validateModuleCompatibility(const ModuleManifest& manifest,
        const Core::RuntimeAPI& api)
    {
        if (api.version().major() > manifest.runtimeVersion.major())
        {
            throw ModuleError(std::format(
                "{} Module: version too old ({}) for runtime ({})",
                manifest.name.getData(),  // TODO: Fix by adding support for String to format
                manifest.runtimeVersion.string(),
                api.version().string()
            ).c_str());
        }
        else if (api.version().minor() > manifest.runtimeVersion.minor())
        {
            m_logger.warn(
                "{} Module: version ({}) older than runtime version ({}), possible incompatibility",
                manifest.name.getData(),  // TODO: Fix by adding support for String to format
                manifest.runtimeVersion.string(),
                api.version().string()
            );
        }
    }
}
