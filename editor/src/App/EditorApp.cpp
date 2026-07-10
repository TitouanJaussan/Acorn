#include "App/EditorApp.hpp"
#include "Layers/ProjectSelectionLayer.hpp"

namespace Acorn::Editor
{
    EditorApp::EditorApp(int argc, char** argv)
        : Core::Application(argc, argv)
    {
        m_engine->pushLayer<ProjectSelectionLayer>(
            m_engine->getLoggerFactory());
    }
}
