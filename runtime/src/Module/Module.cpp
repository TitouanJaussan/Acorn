#include "Acorn/Module/Module.hpp"

namespace Acorn::Module
{
    Module::Module(Runtime::API runtimeAPI, Base::Logger logger)
        : m_logger(std::move(logger)),
          m_api(std::move(runtimeAPI))
    {}
}
