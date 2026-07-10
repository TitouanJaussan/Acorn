#include "Acorn/Core/Application.hpp"
#include "Acorn/Base/Memory/Tracker.hpp"

namespace Acorn::Core
{
    Application::Application(int argc, char** argv)
        : m_engine(UniquePtr<Runtime::Engine>::create(argc, argv))
    {}

    void Application::launch()
    {
        m_engine->run();
        tidyUp();
    }

    void Application::tidyUp()
    {
        m_engine.reset();

        SPDLOG_INFO(
            "Final heap memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getCurrMemUsage()
        );
    }
}
