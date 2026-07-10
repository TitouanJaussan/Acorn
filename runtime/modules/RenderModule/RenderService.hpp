#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP

#include <Acorn/Threading/Service.hpp>
#include <Acorn/Base/Logging/LoggerFactory.hpp>
#include <Acorn/Module/RuntimeModule.hpp>
#include <Acorn/Module/APIHandle.hpp>

#include "Export.hpp"

class RENDER_MODULE_EXPORT RenderService final : public Acorn::Threading::Service
{
public:
    RenderService(
        Acorn::Base::LoggerFactory& factory,
        Acorn::Threading::ThreadingManager& threadingManager,
        Acorn::Module::APIHandle& windowModAPI);

    void work() override;

private:
    Acorn::Module::APIHandle& m_windowModAPI;
};

#endif /* RENDER_SERVICE_HPP */
