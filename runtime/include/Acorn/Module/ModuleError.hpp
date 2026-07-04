#ifndef ACORN_MODULE_ERROR_HPP
#define ACORN_MODULE_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleError final :
        public Core::DetailedError
    {
    public:
        ModuleError(String msg);
    };
}

#endif /* ACORN_MODULE_ERROR_HPP */
