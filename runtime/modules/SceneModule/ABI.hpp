#ifndef SCENE_MODULE_ABI_HPP
#define SCENE_MODULE_ABI_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>

#include "Export.hpp"
#include "API.hpp"

extern "C"
{
    SCENE_MODULE_EXPORT void init(
        Acorn::Runtime::API api,
        Acorn::Base::Logger logger);
    SCENE_MODULE_EXPORT void update();
    SCENE_MODULE_EXPORT void unload();

    SCENE_MODULE_EXPORT SceneModuleAPI* getAPI();
}

#endif /* SCENE_MODULE_ABI_HPP */
