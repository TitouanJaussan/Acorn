#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#include <Acorn/Module/Module.hpp>
#include <Acorn/Module/ModuleManifest.hpp>
#include <Acorn/Templates/UniquePtr.hpp>

#include "API.hpp"
#include "BaseWindow.hpp"

class API_PRIVATE WindowModule final : public Acorn::Module::Module
{
public:
    WindowModule(Acorn::Core::RuntimeAPI api, Acorn::Core::Logger logger);

    void init() override;
    void update() override;
    void unload() override;

private:
    Acorn::UniquePtr<BaseWindow> m_window;
};

extern "C"
{
    Acorn::Module::Module* createModule(Acorn::Core::RuntimeAPI api,
                                        Acorn::Core::Logger logger);
    void destroyModule(Acorn::Module::Module* mod);

    API const Acorn::Module::ModuleManifest* getManifest();
}

#endif /* WINDOW_MODULE_HPP */
