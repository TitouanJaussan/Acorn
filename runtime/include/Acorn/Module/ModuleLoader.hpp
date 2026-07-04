#ifndef ACORN_MODULE_LOADER_HPP
#define ACORN_MODULE_LOADER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Module/ModLoadingCtx.hpp"
#include "Acorn/Module/ModuleManifest.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Templates/Pair.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleLoader
    {
    public:
        ModuleLoader(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsDirPath, ModLoadingCtx ctx);

    private:
        void solveDependencies(
            ArrayList<Pair<std::filesystem::path, ModuleManifest>>& mods,
            size_t modIndex);

        ArrayList<Pair<std::filesystem::path, ModuleManifest>> discoverMods(
            std::filesystem::path modsDirPath,
            ModLoadingCtx& ctx);

        ModuleManifest discoverMod(
            std::filesystem::path modPath,
            ModLoadingCtx& ctx);

        UniquePtr<RuntimeModule> loadModule(
            Pair<std::filesystem::path, ModuleManifest> mod,
            ModLoadingCtx& ctx) noexcept;

        bool isModuleValid(std::filesystem::path modPath);
        void validateModuleCompatibility(
            const ModuleManifest& manifest,
            const Core::RuntimeAPI& api);

        Core::Logger m_logger;
    };
}

#endif /* ACORN_MODULE_LOADER_HPP */
