#ifndef RENDER_MODULE_ABI_HPP
#define RENDER_MODULE_ABI_HPP

#include <Acorn/Core/Runtime/API.hpp>
#include <Acorn/Base/Logging/Logger.hpp>

#include "Export.hpp"
#include "API.hpp"

extern "C"
{
    RENDER_MODULE_EXPORT void init(
        Acorn::Runtime::API api,
        Acorn::Base::Logger logger);
    RENDER_MODULE_EXPORT void update();
    RENDER_MODULE_EXPORT void unload();

    RENDER_MODULE_EXPORT RenderModuleAPI* getAPI();
}

#endif /* RENDER_MODULE_ABI_HPP */
