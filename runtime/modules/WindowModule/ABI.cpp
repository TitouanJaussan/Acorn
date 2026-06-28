#include "ABI.hpp"

#include "glfw/Window.hpp"
#include "glfw/WindowDescriptor.hpp"

static const Acorn::Module::ModuleManifest MANIFEST = 
{
    .name = "Window",
    .runtimeVersion = Acorn::Version::Version{0, 2, 2},
    .dependencies = {}
};

static WindowModule* mod{nullptr};
static WindowModuleAPI* modAPI{nullptr};

void init(
    Acorn::Core::RuntimeAPI runtimeAPI,
    Acorn::Core::Logger logger)
{
    mod = mem_new<WindowModule>(
        std::move(runtimeAPI),
        std::move(logger),
        Acorn::UniquePtr<BaseWindow>(mem_new<GLFW::Window>(
            GLFW::WindowDescriptor
            {
                .factory = runtimeAPI.getLoggerFactory(),
                .title = "Acorn Engine",
                .width = 1200,
                .height = 800
            }
        ))
    );

    modAPI = mem_new<WindowModuleAPI>(mod);
    mod->m_logger.info("Created window mod!");
}

void update()
{
    mod->m_window->pollEvents();
    mod->m_window->swapBuffers();

    if (mod->m_window->shouldClose())
        mod->m_runtimeAPI.stopRuntime();
}

void unload()
{
    mod->m_logger.info("Deleting window mod");

    mem_delete(modAPI);
    mem_delete(mod);

    modAPI = nullptr;
    mod = nullptr;
}

WindowModuleAPI* getAPI()
{
    return modAPI;
}

const Acorn::Module::ModuleManifest* getManifest()
{
    return &MANIFEST;
}
