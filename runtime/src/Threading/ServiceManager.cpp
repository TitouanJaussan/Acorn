#include "Acorn/Threading/ServiceManager.hpp"

namespace Acorn::Threading
{
    ServiceManager::ServiceManager(Base::LoggerFactory& factory)
        : m_logger(factory.create("ServiceManager")),
          m_services()
    {}

    void ServiceManager::addService(UniquePtr<Service> service)
    {
        m_services.append(std::move(service));
    }

    void ServiceManager::shutdown()
    {
        for (UniquePtr<Service>& service: m_services)
        {
            service->stop();
            service->join();
        }

        m_services.clearAll();
    }
}
