#include "Acorn/Threading/ThreadingManagerHandle.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"

namespace Acorn::Threading
{
    ThreadingManagerHandle::ThreadingManagerHandle(
        ThreadingManager& handle) noexcept
        : m_handle(handle)
    {}

    void ThreadingManagerHandle::spawnService(UniquePtr<Service> service)
    {
        m_handle.serviceManager.spawnService(std::move(service), m_handle);
    }

    void ThreadingManagerHandle::submitJob(Job job)
    {
        m_handle.jobScheduler.submitJob(std::move(job));
    }
}
