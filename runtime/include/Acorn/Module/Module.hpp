#ifndef ACORN_MODULE_HPP
#define ACORN_MODULE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Core/Runtime/API.hpp"

namespace Acorn::Module
{
    class ENGINE_API Module
    {
    public:
        Module(Runtime::API runtimeAPI, Base::Logger logger);
        virtual ~Module() {};
        
        virtual void init()   = 0;
        virtual void update() = 0;
        virtual void unload() = 0;

    protected:
        Base::Logger     m_logger;
        Runtime::API m_api;
    };
}

#endif /* ACORN_MODULE_HPP */
