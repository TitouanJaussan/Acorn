#ifndef ACORN_MODULE_LOADER_HPP
#define ACORN_MODULE_LOADER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleLoader
    {
    public:
        ModuleLoader(Core::LoggerFactory factory);

        void loadModules(std::filesystem::path folderPath,
            ModuleRegistry& registry);

    private:
        void loadModule(std::filesystem::path modLibPath,
            ModuleRegistry& registry) noexcept;

        Core::Logger m_logger;
    };
}

#endif /* ACORN_MODULE_LOADER_HPP */
