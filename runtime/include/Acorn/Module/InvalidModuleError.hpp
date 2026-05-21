#ifndef ACORN_INVALID_MODULE_ERROR_HPP
#define ACORN_INVALID_MODULE_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Module
{
    class ENGINE_API InvalidModuleError final :
        public Core::DetailedError
    {
    public:
        InvalidModuleError(const char* msg);
    };
}

#endif /* ACORN_INVALID_MODULE_ERROR_HPP */
