#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP

#include <Acorn/Threading/Service.hpp>
#include <Acorn/Base/Logging/LoggerFactory.hpp>
#include <Acorn/Module/RuntimeModule.hpp>
#include <Acorn/Module/APIHandle.hpp>

#include <WindowModule/API.hpp>
#include <SceneModule/API.hpp>

#include "Export.hpp"

class RENDER_MODULE_EXPORT RenderService final :
    public Acorn::Threading::Service
{
public:
    RenderService(
        Acorn::Base::LoggerFactory& factory,
        Acorn::Module::APIHandle<> windowModAPI,
        Acorn::Module::APIHandle<> sceneModAPI);

    void work() override;

private:
    Acorn::Module::APIHandle<WindowModuleAPI> m_windowModAPI;
    Acorn::Module::APIHandle<SceneModuleAPI>  m_sceneModAPI;
};

#endif /* RENDER_SERVICE_HPP */
