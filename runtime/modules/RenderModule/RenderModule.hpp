#ifndef RENDER_MODULE_HPP
#define RENDER_MODULE_HPP

#include <Acorn/Core/Runtime/RuntimeAPI.hpp>
#include <Acorn/Core/Logging/Logger.hpp>

#include "Export.hpp"

struct RENDER_MODULE_LOCAL RenderModule
{
    Acorn::Core::RuntimeAPI m_runtimeAPI;
    Acorn::Core::Logger m_logger;
};

#endif /* RENDER_MODULE_HPP */
