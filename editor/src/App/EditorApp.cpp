#include "App/EditorApp.hpp"
#include "Layers/ProjectSelectionLayer.hpp"

namespace Acorn::Editor
{
    EditorApp::EditorApp(int argc, const char** argv)
        : Core::Application(argc, argv)
    {
        m_runtime->pushLayer<ProjectSelectionLayer>(
            m_runtime->getLoggerFactory());
    }
}
