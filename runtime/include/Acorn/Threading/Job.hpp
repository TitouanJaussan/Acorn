#ifndef ACORN_JOB_HPP
#define ACORN_JOB_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Threading
{
    struct ENGINE_API Job
    {
        void (*work)(void*){nullptr};
        void (*callback)(void*){nullptr};
        void* data{nullptr};
    };
}

#endif /* ACORN_JOB_HPP */
