#ifndef ACORN_RUNTIME_HPP
#define ACORN_RUNTIME_HPP

#include <atomic>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/Layer/LayerManager.hpp"
#include "Acorn/Module/ModuleManager.hpp"
#include "Acorn/Core/Version/Version.hpp"

namespace Acorn::Core
{
    class ENGINE_API Runtime
    {
    public:
        Runtime(int argc, const char** argv);
        ~Runtime();

        void run();
        void stop();

        template<LayerT T, typename... Args>
        void pushLayer(Args&&... args);

        LoggerFactory& getLoggerFactory() noexcept;

    private:
        RuntimeAPI createAPI();

        // TODO: Pass parsed arguments, not directly raw argc / argv
        void init(int argc, const char** argv);
        void logRuntimeInfo();

    private:
        Version::Version m_version;
        std::atomic_bool m_running;

        LoggerFactory m_loggerFactory;
        Logger m_logger;
        LayerManager m_layerManager;
        Module::ModuleManager m_modManager;
    };
}

#include "Acorn/Core/Runtime/Runtime.ipp"

#endif /* ACORN_RUNTIME_HPP */
