#include "Acorn/Core/Application.hpp"

namespace Acorn::Core
{
    Application::Application(int argc, const char** argv)
        : m_runtime(argc, argv)
    {}

    void Application::launch()
    {
        m_runtime.run();
    }
}
