#ifndef ACORN_THREADING_MANAGER_HANDLE_HPP
#define ACORN_THREADING_MANAGER_HANDLE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Threading/Service.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    class ThreadingManager;

    class ENGINE_API ThreadingManagerHandle final
    {
    public:
        ThreadingManagerHandle(ThreadingManager& handle) noexcept;

        void spawnService(UniquePtr<Service> service);
        void submitJob(Job job);

    private:
        ThreadingManager& m_handle;
    };
}

#endif /* ACORN_THREADING_MANAGER_HANDLE_HPP */
