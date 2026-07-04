#include "Acorn/Core/Version/VersionError.hpp"

namespace Acorn::Version
{
    VersionError::VersionError(String msg)
        : Core::DetailedError("VersionError", std::move(msg))
    {}
}
