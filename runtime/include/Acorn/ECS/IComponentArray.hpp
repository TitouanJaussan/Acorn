#ifndef ACORN_ECS_I_COMPONENT_ARRAY_HPP
#define ACORN_ECS_I_COMPONENT_ARRAY_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn::ECS
{
    class ENGINE_API IComponentArray
    {
    public:
        IComponentArray() = default;
        virtual ~IComponentArray() {};
    };
}

#endif /* ACORN_ECS_I_COMPONENT_ARRAY_HPP */
