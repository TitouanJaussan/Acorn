#include "Acorn/Module/InvalidModuleError.hpp"

namespace Acorn::Module
{
    InvalidModuleError::InvalidModuleError(const char* msg)
        : Core::DetailedError("Invalid Module", msg)
    {}
}
