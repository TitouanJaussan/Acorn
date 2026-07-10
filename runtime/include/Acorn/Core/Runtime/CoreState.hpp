#ifndef ACORN_RUNTIME_CORE_STATE_HPP
#define ACORN_RUNTIME_CORE_STATE_HPP

#include <atomic>
#include <filesystem>

#include "Acorn/EngineAPI.hpp"

#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Layer/LayerManager.hpp"

namespace Acorn::Runtime
{
    struct ENGINE_API CoreState
    {
        Version::Version    version;
        std::atomic_bool    running;
        Base::LoggerFactory loggerFactory;
        Base::Logger        logger;
        Core::LayerManager  layerManager;

        CoreState(std::filesystem::path logFile);
    };
}

#endif /* ACORN_RUNTIME_CORE_STATE_HPP */
