#ifndef SCENE_MODULE_HPP
#define SCENE_MODULE_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>

#include "Export.hpp"
#include "Scene.hpp"

struct SCENE_MODULE_LOCAL SceneModule
{
    Acorn::Runtime::API runtimeAPI;
    Acorn::Base::Logger logger;

    Scene mainScene;
};

#endif /* SCENE_MODULE_HPP */
