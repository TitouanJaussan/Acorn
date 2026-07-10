#ifndef ACORN_MODULE_ERROR_HPP
#define ACORN_MODULE_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/DetailedError.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleError final :
        public Base::DetailedError
    {
    public:
        ModuleError(String msg);
    };
}

#endif /* ACORN_MODULE_ERROR_HPP */
