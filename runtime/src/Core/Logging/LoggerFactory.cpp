#include "Acorn/Core/Logging/LoggerFactory.hpp"

namespace Acorn::Core
{
    LoggerFactory::LoggerFactory(const std::filesystem::path logFile)
        : m_stdoutSink(std::make_shared<
            spdlog::sinks::stdout_color_sink_mt>()),
          m_fileSink(std::make_shared<
            spdlog::sinks::basic_file_sink_mt>(logFile, true)),
          m_defaultLogger(std::make_shared<
            spdlog::logger>("Default", spdlog::sinks_init_list(
            {m_stdoutSink, m_fileSink})))
    {
        const char* pattern = "%H:%M:%S %^%L%$ %n: %v";

        m_stdoutSink->set_pattern(pattern);
        m_fileSink->set_pattern(pattern);

        spdlog::set_default_logger(m_defaultLogger);
    }

    Logger LoggerFactory::create(const char* name)
    {
        return Logger(spdlog::logger(
            name,
            spdlog::sinks_init_list({m_stdoutSink, m_fileSink})
        ));
    }
}
