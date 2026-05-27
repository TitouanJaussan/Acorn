#include "Acorn/Module/Module.hpp"

namespace Acorn::Module
{
    Module::Module(Core::RuntimeAPI runtimeAPI, Core::Logger logger)
        : m_logger(logger),
          m_api(runtimeAPI)
    {}
}
