#ifndef ACORN_SERVICE_DESCRIPTOR_HPP
#define ACORN_SERVICE_DESCRIPTOR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Threading
{
    class ThreadingManager;

    struct ENGINE_API ServiceDescriptor
    {
        String name;
        Base::LoggerFactory& factory;
        ThreadingManager& threadingManager;
    };
}

#endif /* ACORN_SERVICE_DESCRIPTOR_HPP */
