#ifndef ACORN_EDITOR_HPP
#define ACORN_EDITOR_HPP

#include <Acorn/Core/Application.hpp>

namespace Acorn::Editor
{
    class EditorApp final : public Core::Application
    {
    public:
        EditorApp(int argc, char** argv);
    };
}

#endif /* ACORN_EDITOR_HPP */
