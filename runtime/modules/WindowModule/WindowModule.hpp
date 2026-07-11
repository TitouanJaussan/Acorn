#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>
#include <Acorn/Templates/UniquePtr.hpp>

#include "Export.hpp"
#include "BaseWindow.hpp"

struct WINDOW_MODULE_LOCAL WindowModule
{
    Acorn::Runtime::API runtimeAPI;
    Acorn::Base::Logger logger;

    Acorn::UniquePtr<BaseWindow> window;
};

#endif /* WINDOW_MODULE_HPP */
