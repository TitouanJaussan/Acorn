#pragma once

#include "Acorn/Base/Logging/Logger.hpp"

namespace Acorn::Base
{
    template<typename... Args>
    void Logger::info(spdlog::format_string_t<Args...> fmt,
        Args&&... args)
    {
        m_logger.info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Logger::warn(spdlog::format_string_t<Args...> fmt,
        Args&&... args)
    {
        m_logger.warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Logger::error(spdlog::format_string_t<Args...> fmt,
        Args&&... args)
    {
        m_logger.error(fmt, std::forward<Args>(args)...);
    }
}
