#include "Acorn/ECS/ECSManager.hpp"

namespace Acorn::ECS
{
    ECSManager::ECSManager(Base::LoggerFactory& factory)
        : m_logger(factory.create("ECSManager")),
          m_registries()
    {}

    ECSManagerHandle ECSManager::newHandle()
    {
        return ECSManagerHandle(*this);
    }

    Registry& ECSManager::newRegistry()
    {
        return *m_registries.append(
            UniquePtr<Registry>::create(*this)).getPtr();
    }
}
