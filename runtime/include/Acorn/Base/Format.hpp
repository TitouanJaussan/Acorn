#ifndef ACORN_FORMAT_HPP
#define ACORN_FORMAT_HPP

#include <format>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Base
{
    template<typename... Args>
    ENGINE_API String format(std::format_string<Args...> fmt, Args&&... args);
}

#include "Acorn/Base/Format.ipp"

#endif /* ACORN_FORMAT_HPP */
