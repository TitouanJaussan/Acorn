#include "Acorn/Filesystem/FilesystemHandle.hpp"
#include "Acorn/Filesystem/Filesystem.hpp"

namespace Acorn::Filesystem
{
    FilesystemHandle::FilesystemHandle(Filesystem& handle)
        : m_handle(handle)
    {}

    File FilesystemHandle::readFile(std::filesystem::path path,
                                    bool nullTerminated)
    {
        return m_handle.readFile(std::move(path), nullTerminated);
    }
}
