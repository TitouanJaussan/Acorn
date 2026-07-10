#include "Core/SignalHandler.hpp"

static Acorn::Runtime::Engine* enginePtr = nullptr;

#ifdef _WIN32
    #include <Windows.h>

bool WINAPI windows_handler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
        case CTRL_C_EVENT: // Ctrl+C
            runtimePtr->stop();
        case CTRL_BREAK_EVENT: // Ctrl+Break
            break;
        case CTRL_CLOSE_EVENT: // Closing the console window
            break;
        case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
            break;
        case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
            break;
    }

    return FALSE;
}

#else
    #include <signal.h>

void linux_handler(int s)
{
    if (s == 2)
        enginePtr->stop();
}

#endif /* _WIN32 */

/* A rewrite of that file would probably be for the best */

namespace Acorn::Core
{
    void setSignalHandler(Acorn::Runtime::Engine* engine)
    {
        enginePtr = engine;

#ifdef _WIN32
    SetConsoleCtrlHandler(windows_handler, TRUE);
#else
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = linux_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
#endif
    }
}
