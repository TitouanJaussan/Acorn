#ifndef ACORN_MODULE_LOADER_HPP
#define ACORN_MODULE_LOADER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Module/ModLoadingCtx.hpp"
#include "Acorn/Module/ModuleManifest.hpp"
#include "Acorn/Templates/UniquePtr.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleLoader
    {
    public:
        ModuleLoader(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsDirPath, ModLoadingCtx ctx);

    private:
        void solveDependencies(
            ArrayList<UniquePtr<RuntimeModule>>& mods,
            size_t modIndex);

        ArrayList<std::filesystem::path> discoverMods(
            std::filesystem::path modsDirPath,
            ModLoadingCtx ctx);
        UniquePtr<RuntimeModule> loadModule(
            std::filesystem::path modPath,
            ModLoadingCtx ctx) noexcept;
        
        void validateModuleCompatibility(const ModuleManifest& manifest,
            const Core::RuntimeAPI& api);

        Core::Logger m_logger;
    };
}

#endif /* ACORN_MODULE_LOADER_HPP */
