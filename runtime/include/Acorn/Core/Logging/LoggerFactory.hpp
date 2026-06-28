#ifndef ACORN_LOGGER_FACTORY_HPP
#define ACORN_LOGGER_FACTORY_HPP

#include <filesystem>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Core
{
    class ENGINE_API LoggerFactory
    {
    public:
        LoggerFactory(const std::filesystem::path logFile);

        Logger create(String name);

    private:
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_stdoutSink;
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
        std::shared_ptr<spdlog::logger> m_defaultLogger;
    };
}

#endif /* ACORN_LOGGER_FACTORY_HPP */
