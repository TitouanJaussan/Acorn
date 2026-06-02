#ifndef RENDER_MODULE_HPP
#define RENDER_MODULE_HPP

#include <Acorn/Module/Module.hpp>
#include <Acorn/Module/ModuleManifest.hpp>
#include <Acorn/Core/Runtime/RuntimeAPI.hpp>

#include "API.hpp"

class RenderModule final : public Acorn::Module::Module
{
public:
    RenderModule(Acorn::Core::RuntimeAPI api, Acorn::Core::Logger logger);

    void init() override;
    void update() override;
    void unload() override;
};

extern "C"
{
    API Acorn::Module::Module* createModule(
        Acorn::Core::RuntimeAPI api,
        Acorn::Core::Logger logger);
    API void destroyModule(Acorn::Module::Module* mod);
    API const Acorn::Module::ModuleManifest* getManifest();
}

#endif /* RENDER_MODULE_HPP */
