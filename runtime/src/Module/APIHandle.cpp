#include "Acorn/Module/APIHandle.hpp"

namespace Acorn::Module
{
    APIHandle::APIHandle(void* ptr)
        : m_apiPtr(ptr)
    {}

    void APIHandle::update(void* newApiPtr)
    {
        m_apiPtr = newApiPtr;
    }
}
