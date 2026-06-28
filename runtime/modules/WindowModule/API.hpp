#ifndef WINDOW_MODULE_API_HPP
#define WINDOW_MODULE_API_HPP

#include "Export.hpp"
#include "BaseWindow.hpp"
#include "WindowModule.hpp"

class WINDOW_MODULE_EXPORT WindowModuleAPI
{
public:
    WindowModuleAPI(WindowModule* mod);

    BaseWindow* getMainWindow();

private:
    WindowModule* m_module;
};

#endif /* WINDOW_MODULE_API_HPP */
