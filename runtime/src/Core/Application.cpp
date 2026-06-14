#include "Acorn/Core/Application.hpp"
#include "Acorn/Core/Memory/Tracker.hpp"

namespace Acorn::Core
{
    Application::Application(int argc, const char** argv)
        : m_runtime(UniquePtr<Core::Runtime>::create(argc, argv))
    {}

    void Application::launch()
    {
        m_runtime->run();
        tidyUp();
    }

    void Application::tidyUp()
    {
        m_runtime.reset();

        SPDLOG_INFO(
            "Final heap memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getCurrMemUsage()
        );
    }
}
