#include "WindowModule.hpp"
#include "Acorn/Module/Module.hpp"
#include "glfw/Window.hpp"
#include "glfw/WindowDescriptor.hpp"

static const Acorn::Module::ModuleManifest MANIFEST = 
{
    .name = "Window",
    .runtimeVersion = Acorn::Version::Version{0, 0, 1},

    .dependencies = nullptr,
    .dependenciesCount = 0
};

WindowModule::WindowModule(Acorn::Core::RuntimeAPI api,
                           Acorn::Core::Logger logger)
    : Acorn::Module::Module(api, logger),
      m_window(new GLFW::Window(GLFW::WindowDescriptor{
          .moduleLogger = m_logger,
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
    return new WindowModule{api, logger}; // TODO: Replace with mem_new & mem_delete
}

void destroyModule(Acorn::Module::Module* mod)
{
    delete mod;
}

const Acorn::Module::ModuleManifest* getManifest()
{
    return &MANIFEST;
}
