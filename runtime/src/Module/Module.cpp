#include <format>

#include "Acorn/Module/Module.hpp"
#include "Acorn/Module/ModuleError.hpp"

namespace Acorn::Module
{
    Module::Module(ModuleDescriptor descriptor)
        : m_lib(descriptor.libPath),
          name((decltype(name))m_lib.resolveSymbol("name")),
          load((decltype(load))m_lib.resolveSymbol("load")),
          update((decltype(update))m_lib.resolveSymbol("update")),
          render((decltype(render))m_lib.resolveSymbol("render")),
          unload((decltype(unload))m_lib.resolveSymbol("unload"))
    {
        const auto filename = descriptor.libPath.filename().string();

        if (!name)
            throw ModuleError(
                std::format(
                    "Unnamed module ({}): missing 'name' symbol.",
                    filename
                ).c_str()
            );

        if (!load)
            throw ModuleError(
                std::format(
                    "Module '{}' ({}): missing 'load'",
                    name,
                    filename
                ).c_str()
            );

        if (!update)
            throw ModuleError(
                std::format(
                    "Module '{}' ({}): missing 'update'",
                    name,
                    filename
                ).c_str()
            );

        if (!render)
            throw ModuleError(
                std::format(
                    "Module '{}' ({}): missing 'render'",
                    name,
                    filename
                ).c_str()
            );

        if (!unload)
            throw ModuleError(
                std::format(
                    "Module '{}' ({}): missing 'unload'",
                    name,
                    filename
                ).c_str()
            );
    }

    std::filesystem::path Module::libPath() const noexcept
    {
        return m_lib.path;
    }
}
