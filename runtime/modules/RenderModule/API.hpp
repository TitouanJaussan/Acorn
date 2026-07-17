#ifndef RENDER_MODULE_API_HPP
#define RENDER_MODULE_API_HPP

#include "Export.hpp"
#include "RenderModule.hpp"

class RENDER_MODULE_EXPORT RenderModuleAPI
{
public:
    RenderModuleAPI(RenderModule* mod);

private:
    RenderModule* m_mod;
};

#endif /* RENDER_MODULE_API_HPP */
