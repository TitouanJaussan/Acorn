#include "Acorn/Module/ModuleError.hpp"

namespace Acorn::Module
{
    ModuleError::ModuleError(const char* msg)
        : Core::DetailedError(" Module", msg)
    {}
}
