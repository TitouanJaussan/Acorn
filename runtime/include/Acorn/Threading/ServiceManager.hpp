#ifndef ACORN_SERVICE_MANAGER_HPP
#define ACORN_SERVICE_MANAGER_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Threading/Service.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ServiceManager
    {
    public:
        ServiceManager(Base::LoggerFactory& factory);

        void addService(UniquePtr<Service> service);
        void shutdown();

    private:
        Base::Logger m_logger;

        ArrayList<UniquePtr<Service>> m_services;
    };
}

#endif /* ACORN_SERVICE_MANAGER_HPP */
