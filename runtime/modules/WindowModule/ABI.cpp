#include "ABI.hpp"

#include "glfw/Window.hpp"
#include "glfw/WindowDescriptor.hpp"

static WindowModule*    mod{nullptr};
static WindowModuleAPI* modAPI{nullptr};

void init(
    Acorn::Runtime::API runtimeAPI,
    Acorn::Base::Logger logger)
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
    mod->logger.info("Created window mod!");
}

void update()
{
    mod->window->pollEvents();

    if (mod->window->shouldClose())
        mod->runtimeAPI.stopEngine();
}

void unload()
{
    mod->logger.info("Deleting window mod");

    mem_delete(modAPI);
    mem_delete(mod);

    modAPI = nullptr;
    mod    = nullptr;
}

WindowModuleAPI* getAPI()
{
    return modAPI;
}
