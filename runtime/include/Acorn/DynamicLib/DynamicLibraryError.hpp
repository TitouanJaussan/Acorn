#ifndef ACORN_DYNAMIC_LIBRARY_ERROR_HPP
#define ACORN_DYNAMIC_LIBRARY_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/DetailedError.hpp"

namespace Acorn::Lib
{
    class ENGINE_API DynamicLibraryError final : public Base::DetailedError
    {
    public:
        DynamicLibraryError(String msg);
    };
}

#endif /* ACORN_DYNAMIC_LIBRARY_ERROR_HPP */
