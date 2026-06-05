#ifndef ACORN_SERVICE_MANAGER_HPP
#define ACORN_SERVICE_MANAGER_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Threading/Service.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ServiceManager
    {
    public:
        ServiceManager(Core::LoggerFactory& factory);

        void addService(UniquePtr<Service> service);
        void shutdown();

    private:
        Core::Logger m_logger;

        ArrayList<UniquePtr<Service>> m_services;
    };
}

#endif /* ACORN_SERVICE_MANAGER_HPP */
