#include "Acorn/Core/Runtime/Systems.hpp"

namespace Acorn::Runtime
{
    Systems::Systems(Base::LoggerFactory& factory,
                     std::filesystem::path rootDirectory)
        : filesystem(factory, std::move(rootDirectory)),
          threadingManager(factory),
          modManager(factory)
    {}
}
