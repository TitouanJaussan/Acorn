#include "Acorn/Module/ModuleError.hpp"

namespace Acorn::Module
{
    ModuleError::ModuleError(String msg)
        : Core::DetailedError("Module", std::move(msg))
    {}
}
