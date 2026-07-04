#ifndef ACORN_VERSION_ERROR_HPP
#define ACORN_VERSION_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Version
{
    class ENGINE_API VersionError final : public Core::DetailedError
    {
    public:
        VersionError(String msg);
    };
}

#endif /* ACORN_VERSION_ERROR_HPP */
