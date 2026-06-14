#include <Acorn/Module/Module.hpp>
#include <Acorn/Core/Memory/Mem.hpp>

#include "WindowModule.hpp"
#include "glfw/Window.hpp"
#include "glfw/WindowDescriptor.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

static const Acorn::Module::ModuleManifest MANIFEST = 
{
    .name = "Window",
    .runtimeVersion = Acorn::Version::Version{0, 2, 1},

    .dependencies = {}
};

WindowModule::WindowModule(Acorn::Core::RuntimeAPI api,
                           Acorn::Core::Logger logger)
    : Acorn::Module::Module(std::move(api), std::move(logger)),
      m_window(mem_new<GLFW::Window>(GLFW::WindowDescriptor{
          .factory = m_api.getLoggerFactory(),
          .title = "Acorn Engine",
          .width = 1200,
          .height = 800
      }))
{}

void WindowModule::init()
{
    m_logger.info("Created Window Module!");
}

void WindowModule::update()
{
    m_window->pollEvents();
    m_window->swapBuffers();

    if (m_window->shouldClose())
        m_api.stopRuntime();
}

void WindowModule::unload()
{
    m_logger.info("Shutting down Window Module!");
}

Acorn::Module::Module* createModule(Acorn::Core::RuntimeAPI api,
                                    Acorn::Core::Logger logger)
{
    return mem_new<WindowModule>(api, logger);
}

void destroyModule(Acorn::Module::Module* mod)
{
    mem_delete(mod);
}

const Acorn::Module::ModuleManifest* getManifest()
{
    return &MANIFEST;
}
