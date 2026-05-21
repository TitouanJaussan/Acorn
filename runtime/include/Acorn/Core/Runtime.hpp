#ifndef ACORN_RUNTIME_HPP
#define ACORN_RUNTIME_HPP

#include <memory>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Layer/LayerManager.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Window/Window.hpp"

namespace Acorn::Core
{
    class ENGINE_API Runtime
    {
    public:
        Runtime(int argc, const char** argv);
        ~Runtime();

        void run();

        template<LayerT T, typename... Args>
        void pushLayer(Args&&... args);

        LoggerFactory& getLoggerFactory() noexcept;

    private:
        void modulesLoad();
        void modulesUpdate();
        void modulesRender();
        void modulesUnload();

        void modulesForEach(void (*func)(Module::Module&));

        LoggerFactory m_loggerFactory;
        Logger m_logger;
        LayerManager m_layerManager;
        Module::ModuleLoader m_modLoader;
        Module::ModuleRegistry m_modRegistry;

        // TODO: This is wrong
        std::unique_ptr<Window::BaseWindow> m_window;
    };
}

#include "Acorn/Core/Runtime.ipp"

#endif /* ACORN_RUNTIME_HPP */
