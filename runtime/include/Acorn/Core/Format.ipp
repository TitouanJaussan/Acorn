#pragma once

#include "Acorn/Core/Format.hpp"
#include "Acorn/Templates/StringOutputIterator.hpp"

namespace Acorn::Core
{
    template<typename... Args>
    String format(std::format_string<Args...> fmt, Args&&... args)
    {
        String result{};

        std::format_to(
            StringOutputIterator(&result),
            fmt,
            std::forward<Args>(args)...
        );

        return result;
    }
}
