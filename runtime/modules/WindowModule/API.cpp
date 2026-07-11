#include "API.hpp"

#include "WindowModule.hpp"
#include "API.hpp"

WindowModuleAPI::WindowModuleAPI(WindowModule* mod)
    : m_module(mod)
{}

BaseWindow* WindowModuleAPI::getMainWindow()
{
    return m_module->window.getPtr();
}
