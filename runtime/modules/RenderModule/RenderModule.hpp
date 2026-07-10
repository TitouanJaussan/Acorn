#ifndef RENDER_MODULE_HPP
#define RENDER_MODULE_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>

#include "Export.hpp"

struct RENDER_MODULE_LOCAL RenderModule
{
    Acorn::Runtime::API m_runtimeAPI;
    Acorn::Base::Logger m_logger;
};

#endif /* RENDER_MODULE_HPP */
