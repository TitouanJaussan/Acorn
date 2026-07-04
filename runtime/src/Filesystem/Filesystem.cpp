#include <climits>
#include <fstream>

#include "Acorn/Filesystem/Filesystem.hpp"
#include "Acorn/Filesystem/FilesystemError.hpp"

namespace Acorn::Filesystem
{
    Filesystem::Filesystem(Core::LoggerFactory& factory,
                           std::filesystem::path rootDirectory)
        : m_logger(factory.create("Filesystem"))
    {
        static_assert(CHAR_BIT == 8);
        std::filesystem::current_path(rootDirectory);
        m_logger.info("Set root directory to {}", rootDirectory.string());
    }

    File Filesystem::readFile(std::filesystem::path path,
                              bool nullTerminated)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
            throw FilesystemError(String("Could not read file: ") + String(path.c_str()));

        const size_t size = file.tellg();
        char* buff = (char*)op_new(size + static_cast<size_t>(nullTerminated));

        file.seekg(0);
        file.read(buff, size);

        if (nullTerminated)
            buff[size] = '\0';

        file.close();

        return File{std::move(path), ArrayList<char>(buff, size)};
    }
}
