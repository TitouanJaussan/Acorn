#ifndef ACORN_LOGGER_HPP
#define ACORN_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <tui/tblocks.hpp> // My litte lib ♥

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Core
{
    class ENGINE_API Logger
    {
    public:
        Logger();
        Logger(spdlog::logger logger);

        template<typename... Args>
        void info(spdlog::format_string_t<Args...> fmt,
            Args&&... args);

        template<typename... Args>
        void warn(spdlog::format_string_t<Args...> fmt,
            Args&&... args);
        
        template<typename... Args>
        void error(spdlog::format_string_t<Args...> fmt,
            Args&&... args);

        // tblocks compatibility overloads
        void info(const tui::Block block);
        void warn(const tui::Block block);
        void error(const tui::Block block);

    private:
        spdlog::logger m_logger;
    };
}

#include "Acorn/Core/Logging/Logger.ipp"

#endif /* ACORN_LOGGER_HPP */

