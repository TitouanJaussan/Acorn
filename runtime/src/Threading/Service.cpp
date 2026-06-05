#include "Acorn/Threading/Service.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"

namespace Acorn::Threading
{
    Service::Service(ServiceDescriptor desc)
        : name(desc.name),
          m_logger(desc.factory.create(name)),
          m_running(true),
          m_thread(desc.threadingManager.queryNewThread(
            [this]() -> void { work(); }
          ))
    {}

    void Service::stop()
    {
        m_running = false;
    }

    void Service::join()
    {
        m_thread.join();
    }
}
