#include "App/EditorApp.hpp"

int main(int argc, char** argv)
{
    Acorn::Editor::EditorApp editor{argc, argv};
    editor.launch();

    return 0;
}
