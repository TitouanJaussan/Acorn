#ifndef ACORN_ECS_MANAGER_HPP
#define ACORN_ECS_MANAGER_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/ECS/Registry.hpp"
#include "Acorn/ECS/ECSManagerHandle.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"

namespace Acorn::ECS
{
    class ENGINE_API ECSManager
    {
    public:
        ECSManager(Base::LoggerFactory& factory);

        ECSManagerHandle newHandle();
        Registry createRegistry();

    private:
        Base::Logger m_logger;
    };
}

#endif /* ACORN_ECS_MANAGER_HPP */
