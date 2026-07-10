#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>
#include <Acorn/Templates/UniquePtr.hpp>

#include "Export.hpp"
#include "BaseWindow.hpp"

struct WINDOW_MODULE_LOCAL WindowModule
{
    Acorn::Runtime::API m_runtimeAPI;
    Acorn::Base::Logger m_logger;

    Acorn::UniquePtr<BaseWindow> m_window;
};

#endif /* WINDOW_MODULE_HPP */
