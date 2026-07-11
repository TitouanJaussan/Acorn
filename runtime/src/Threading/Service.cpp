#include "Acorn/Threading/Service.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"
#include "Acorn/Base/DetailedError.hpp"

namespace Acorn::Threading
{
    Service::Service(ServiceDescriptor desc)
        : name(desc.name),
          m_logger(desc.factory.create(name + " Service")),
          m_running(true),
          m_thread()
    {}

    bool Service::start(ThreadingManager& manager)
    {
        try
        {
            m_thread = manager.queryNewThread([this]() -> void { work(); });
            return true;
        }
        catch (const Base::DetailedError& err)
        {
            m_logger.info("Failed to start: {}", err.what());
            return false;
        }
    }

    void Service::stop()
    {
        m_running = false;
    }

    void Service::join()
    {
        m_thread.join();
    }
}
