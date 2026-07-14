#include "Acorn/ECS/ECSManager.hpp"

namespace Acorn::ECS
{
    ECSManager::ECSManager(Base::LoggerFactory& factory)
        : m_logger(factory.create("ECSManager"))
    {}

    ECSManagerHandle ECSManager::newHandle()
    {
        return ECSManagerHandle(*this);
    }

    Registry ECSManager::createRegistry()
    {
        return Registry{};
    }
}
