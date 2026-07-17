#ifndef ACORN_SCENE_HPP
#define ACORN_SCENE_HPP

#include <Acorn/ECS/Registry.hpp>

#include "Export.hpp"

class SCENE_MODULE_LOCAL Scene
{
public:
    Scene(Acorn::ECS::Registry& registry);

private:
    Acorn::ECS::Registry& m_registry;
};

#endif /* ACORN_SCENE_HPP */
