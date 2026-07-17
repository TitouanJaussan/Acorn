#include "ABI.hpp"

static SceneModule*    mod{nullptr};
static SceneModuleAPI* modAPI{nullptr};

void init(
    Acorn::Runtime::API api,
    Acorn::Base::Logger logger)
{
    mod = mem_new<SceneModule>(
        api,
        std::move(logger),
        Scene(api.ecs().newRegistry()));
    modAPI = mem_new<SceneModuleAPI>(mod);
}

void update()
{

}

void unload()
{
    mem_delete(modAPI);
    mem_delete(mod);

    modAPI = nullptr;
    mod = nullptr;
}

SceneModuleAPI* getAPI()
{
    return modAPI;
}
