#ifndef ACORN_JOB_SCHEDULER_DESCRIPTOR_HPP
#define ACORN_JOB_SCHEDULER_DESCRIPTOR_HPP

#include <cstdint>
#include <cstddef>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"

namespace Acorn::Threading
{
    struct ENGINE_API JobSchedulerDescriptor
    {
        Core::LoggerFactory loggerFactory;

        const size_t workerThreadsCount{0};
        const uint32_t maxCallbacksPerFrame{1};
        const float frameCallbackBudget_ms{4.0f};
    };
}

#endif /* ACORN_JOB_SCHEDULER_DESCRIPTOR_HPP */
