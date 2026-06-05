#include "Acorn/Module/Module.hpp"

namespace Acorn::Module
{
    Module::Module(Core::RuntimeAPI runtimeAPI, Core::Logger logger)
        : m_logger(std::move(logger)),
          m_api(std::move(runtimeAPI))
    {}
}
