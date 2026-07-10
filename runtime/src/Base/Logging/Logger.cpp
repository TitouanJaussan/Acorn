#include "Acorn/Base/Logging/Logger.hpp"

namespace Acorn::Base
{
    Logger::Logger()
        : m_logger("<Default>")
    {}
    Logger::Logger(spdlog::logger logger)
        : m_logger(logger)
    {};

    void Logger::info(const tui::Block block)
    {
        for (const auto& line: block.lines)
            m_logger.info(line);
    }

    void Logger::warn(const tui::Block block)
    {
        for (const auto& line: block.lines)
            m_logger.warn(line);
    }

    void Logger::error(const tui::Block block)
    {
        for (const auto& line: block.lines)
            m_logger.error(line);
    }
}
