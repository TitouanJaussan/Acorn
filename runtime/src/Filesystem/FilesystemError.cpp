#include "Acorn/Filesystem/FilesystemError.hpp"

namespace Acorn::Filesystem
{
    FilesystemError::FilesystemError(String msg)
        : Core::DetailedError("Filesystem", std::move(msg))
    {}
}
