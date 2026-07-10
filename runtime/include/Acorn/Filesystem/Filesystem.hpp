#ifndef ACORN_FILESYSTEM_HPP
#define ACORN_FILESYSTEM_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Filesystem/File.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"

namespace Acorn::Filesystem
{
    class ENGINE_API Filesystem
    {
    public:
        Filesystem(Base::LoggerFactory& factory,
                   std::filesystem::path rootDirectory);
        
        File readFile(std::filesystem::path path,
                      bool nullTerminated = false);

    private:
        Base::Logger m_logger;
    };
}

#endif /* ACORN_FILESYSTEM_HPP */
