#ifndef ACORN_MODULE_HPP
#define ACORN_MODULE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Core/Runtime/RuntimeAPI.hpp"

namespace Acorn::Module
{
    class ENGINE_API Module
    {
    public:
        Module(Core::RuntimeAPI runtimeAPI, Core::Logger logger);
        virtual ~Module() {};
        
        virtual void init()   = 0;
        virtual void update() = 0;
        virtual void unload() = 0;

    protected:
        Core::Logger     m_logger;
        Core::RuntimeAPI m_api;
    };
}

#endif /* ACORN_MODULE_HPP */
