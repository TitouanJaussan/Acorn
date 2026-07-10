#include "Acorn/Base/Version/VersionError.hpp"

namespace Acorn::Version
{
    VersionError::VersionError(String msg)
        : Base::DetailedError("VersionError", std::move(msg))
    {}
}
