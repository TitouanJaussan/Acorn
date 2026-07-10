#include "Acorn/Core/Runtime/CoreState.hpp"
#include "Acorn/Version/RuntimeVersion.hpp"

namespace Acorn::Runtime
{
    CoreState::CoreState(std::filesystem::path logFile)
        : version(RUNTIME_VERSION_MAJOR,
                  RUNTIME_VERSION_MINOR,
                  RUNTIME_VERSION_PATCH),
          running(true),
          loggerFactory(std::move(logFile)),
          logger(loggerFactory.create("Engine")),
          layerManager(loggerFactory)
    {}
}
