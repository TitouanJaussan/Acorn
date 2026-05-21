#include "Acorn/Core/Runtime.hpp"

#include "Window/glfw/Window.hpp"

namespace Acorn::Core
{
    Runtime::Runtime(int argc, const char** argv)
        : m_loggerFactory("log.txt"),
          m_logger(m_loggerFactory.create("Runtime")),
          m_layerManager(),
          m_modLoader(getLoggerFactory()),
          m_modRegistry(m_logger),
          m_window(new Window::GLFW::Window(
            Window::GLFW::WindowDescriptor{
                .loggerFactory = m_loggerFactory,
                .title = "Acorn Engine",
                .width = 1200,
                .height = 800
            }))
    {
        // TODO: Make this a proper fix
        std::filesystem::current_path(std::filesystem::absolute(argv[0]).parent_path());

        m_modLoader.loadModules("modules/", m_modRegistry);

        modulesLoad();
    }

    Runtime::~Runtime()
    {
        m_logger.info("Shutting down runtime...");
    }

    void Runtime::run()
    {
        while (!m_window->shouldClose())
        {
            modulesUpdate();
            modulesRender();
            m_window->swapBuffers();
            m_window->pollEvents();
        }

        modulesUnload();
    }

    LoggerFactory& Runtime::getLoggerFactory() noexcept
    {
        return m_loggerFactory;
    }

    void Runtime::modulesLoad()
    {
        modulesForEach([](Module::Module& mod)
        {
            mod.load();
        });
    }
    
    void Runtime::modulesUpdate()
    {
        modulesForEach([](Module::Module& mod)
        {
            mod.update();
        });
    }

    void Runtime::modulesRender()
    {
        modulesForEach([](Module::Module& mod)
        {
            mod.render();
        });
    }

    void Runtime::modulesUnload()
    {
        modulesForEach([](Module::Module& mod)
        {
            mod.unload();
        });
    }

    void Runtime::modulesForEach(void (*func)(Module::Module&))
    {
        for (const auto& mod: m_modRegistry.getModules())
            func(*mod);
    }
}
