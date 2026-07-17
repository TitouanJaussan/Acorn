#ifndef ACORN_ECS_MANAGER_HANDLE_HPP
#define ACORN_ECS_MANAGER_HANDLE_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn::ECS
{
    class ECSManager;
    class Registry;

    class ENGINE_API ECSManagerHandle
    {
    public:
        ECSManagerHandle(ECSManager& handle);

        Registry& newRegistry();

    private:
        ECSManager& m_handle;
    };
}

#endif /* ACORN_ECS_MANAGER_HANDLE_HPP */
