#ifndef ACORN_SERVICE_HPP
#define ACORN_SERVICE_HPP

#include <atomic>
#include <thread>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Threading/ServiceDescriptor.hpp"
#include "Acorn/Base/Logging/Logger.hpp"

namespace Acorn::Threading
{
    class ThreadingManager;

    // Maybe this could be factored out with the WorkerThread class
    // by giving them a mutual base class, like a threading base class
    class ENGINE_API Service
    {
    public:
        Service(ServiceDescriptor descriptor);
        virtual ~Service() = default;

        Service(Service&&)                 = delete;
        Service(const Service&)            = delete;
        Service& operator=(Service&&)      = delete;
        Service& operator=(const Service&) = delete;

        bool start(ThreadingManager& manager);
        void stop();
        void join();

        const String name;

    protected:
        virtual void work() = 0;

        Base::Logger m_logger;
        std::atomic_bool m_running;

    private:
        std::thread m_thread;
    };
}

#endif /* ACORN_SERVICE_HPP */
