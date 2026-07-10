#include "Acorn/Filesystem/FilesystemError.hpp"

namespace Acorn::Filesystem
{
    FilesystemError::FilesystemError(String msg)
        : Base::DetailedError("Filesystem", std::move(msg))
    {}
}
