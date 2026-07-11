#include <filesystem>
#define TOML_IMPLEMENTATION
#include <tomlplusplus/toml.hpp>

#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/Module/ModuleError.hpp"
#include "Acorn/Toml/ToArrayList.hpp"

namespace Acorn::Module
{
    ModuleLoader::ModuleLoader(Base::LoggerFactory& factory)
        : m_logger(factory.create("ModLoader"))
    {}

    void ModuleLoader::loadModules(std::filesystem::path modsDirPath,
                                   ModLoadingCtx ctx)
    {
        auto modsList = discoverMods(modsDirPath, ctx);

        for (size_t i = 0; i < modsList.getSize(); ++i)
            solveDependencies(modsList, i);

        for (auto& mod: modsList)
        {
            auto loaded = loadModule(std::move(mod), ctx);
            if (!loaded) continue;
            ctx.modRegistry.registerModule(std::move(loaded));
        }
    }

    void ModuleLoader::solveDependencies(
        ArrayList<Pair<std::filesystem::path, ModuleManifest>>& mods,
        size_t modIndex)
    {
        while (modIndex < mods.getSize())
        {
            size_t totalSolvedDeps = 0;

            for (size_t depIdx = 0;
                 depIdx < mods[modIndex].m_second.dependencies.getSize();
                 ++depIdx)
            {
                size_t foundIdx = mods.findIndex(
                    [](auto& mod, auto& mods, auto currModIndex, auto depIdx)
                        -> bool
                    {
                        return mod.m_second.name ==
                               mods[currModIndex].m_second.dependencies[depIdx];
                    }, mods, modIndex, depIdx
                );

                if (foundIdx == mods.getSize())
                {
                    // Dependency not here, let's not load this mod
                    m_logger.error(
                        "Could not solve dependencies for the {} module"
                        " (missing {} module), loading aborted.",
                        mods[modIndex].m_second.name,
                        mods[modIndex].m_second.dependencies[depIdx]
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
                break;  // Or return
        }
    }

    ArrayList<Pair<std::filesystem::path,
                   ModuleManifest>> ModuleLoader::discoverMods(
        std::filesystem::path modsDirPath,
        ModLoadingCtx& ctx)
    {
        ArrayList<Pair<std::filesystem::path, ModuleManifest>> modPaths{};

        if (!std::filesystem::exists(modsDirPath))
        {
            m_logger.warn(
                "{} doesn't exist, no modules will be loaded",
                modsDirPath.c_str());
            return {};
        }

        if (!std::filesystem::is_directory(modsDirPath))
        {
            m_logger.warn(
                "{} is not a directory, no modules will be loaded",
                modsDirPath.c_str());
        }

        for (const auto& item: std::filesystem::directory_iterator(modsDirPath))
        {
            try
            {
                if (!std::filesystem::is_directory(item))
                {
                    m_logger.warn(
                        "Unexpected file in modules folder ('{}')",
                        item.path().filename().string());
                    continue;
                }

                ModuleManifest manifest = discoverMod(item.path(), ctx);
                validateModuleCompatibility(manifest, ctx.runtimeAPI);

                modPaths.append(Pair{
                    item.path(),
                    manifest
                });
            }
            catch (const Base::DetailedError& err)
            {
                m_logger.error(
                    "Invalid module '{}', loading aborted: {}",
                    item.path().filename().string(),
                    err.what()
                );
            }
        }

        return modPaths;
    }

    ModuleManifest ModuleLoader::discoverMod(
        std::filesystem::path modPath,
        ModLoadingCtx& ctx)
    {
        const auto manifestPath = modPath / "manifest.toml";

        if (!std::filesystem::exists(manifestPath))
        {
            throw ModuleError(Base::format(
                "No manifest.toml found in module directory '{}'",
                modPath.string()
            ));
        }

        Filesystem::File manifestFile = ctx.filesystem.readFile(
            manifestPath, true);
        toml::table manifestTable{};
        
        try
        {
            manifestTable = toml::parse(
                manifestFile.getData(),
                manifestPath.string());
        }
        catch (const toml::parse_error& err)
        {
            throw ModuleError(Base::format(
                "Failed to parse {}: {}",
                manifestPath.string(),
                err.what()
            ));
        }

        if (!manifestTable.contains("name") or
            !manifestTable["name"].is_string())
        {
            throw ModuleError(Base::format(
                "Missing or invalid 'name' field in '{}",
                manifestPath.string()
            ));
        }

        if (!manifestTable.contains("version") or
            !manifestTable["version"].is_array())
        {
            throw ModuleError(Base::format(
                "Missing or invalid 'version' field in '{}'",
                manifestPath.string()
            ));
        }

        if (!manifestTable.contains("dependencies") or
            !manifestTable["dependencies"].is_array())
        {
            throw ModuleError(Base::format(
                "Missing or invalid 'dependencies' field in '{}'",
                manifestPath.string()
            ));
        }

        return ModuleManifest
        {
            .name = String(manifestTable["name"].as_string()->get().c_str()),
            .runtimeVersion = Version::Version(Toml::toIntArrayList(
                    manifestTable["version"].as_array()
                )),
            .dependencies = Toml::toStringArrayList(
                manifestTable["dependencies"].as_array())
        };

    }

    UniquePtr<RuntimeModule> ModuleLoader::loadModule(
        Pair<std::filesystem::path, ModuleManifest> mod,
        ModLoadingCtx& ctx) noexcept
    {
        size_t sharedLibrariesCount{0};
        std::filesystem::path libPath{};

        for (const auto& item: std::filesystem::directory_iterator(mod.m_first))
        {
            if (std::filesystem::is_directory(item))
                continue;

#ifdef _WIN32
            if (item.path().filename().extension() == ".dll")
            {
                libPath = item.path();
                ++sharedLibrariesCount;
            }
#else
            if (item.path().filename().extension() == ".so")
            {
                libPath = item.path();
                ++sharedLibrariesCount;
            }
#endif /* _WIN32 */
        }

        if (sharedLibrariesCount == 0)
        {
            m_logger.error(
                "No shared libraries found in module directory '{}',"
                " module loading aborted",
                mod.m_first.filename().string());
            return {};
        }

        if (sharedLibrariesCount > 1)
        {
            m_logger.error(
                "More than 1 shared library found in module directory '{}',"
                " module loading aborted",
                mod.m_first.filename().string());
            return {};
        }

        try
        {
            UniquePtr<RuntimeModule> modInstance =
                UniquePtr<RuntimeModule>::create(RuntimeModuleDescriptor
                    {
                        .lib = Lib::DynamicLibrary{libPath},
                        .manifest = std::move(mod.m_second),
                    }
                );

            return modInstance;
        }
        catch (const Base::DetailedError& err)
        {
            m_logger.error("Couldn't load module '{}': {}",
                mod.m_first.filename().string(),
                err.what()
            );
        }

        return {};
    }

    void ModuleLoader::validateModuleCompatibility(
        const ModuleManifest& manifest,
        const Runtime::API& api)
    {

        const auto& ver = api.getVersion();

        if (ver.major() > manifest.runtimeVersion.major())
        {
            throw ModuleError(Base::format(
                "{} Module: version too old ({}) for runtime ({})",
                manifest.name.getData(),  // TODO: Fix by adding support for String to format
                manifest.runtimeVersion.string(),
                ver.string()
            ));
        }
        else if (ver.minor() > manifest.runtimeVersion.minor())
        {
            m_logger.warn(
                "{} Module: version ({}) older than runtime version ({}), "
                "possible incompatibility",
                manifest.name.getData(),  // TODO: Fix by adding support for String to format
                manifest.runtimeVersion.string(),
                ver.string()
            );
        }
    }
}
