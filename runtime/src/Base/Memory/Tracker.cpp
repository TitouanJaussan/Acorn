#include "Acorn/Base/Memory/Tracker.hpp"
#include "Acorn/Base/Assert.hpp"

namespace Acorn::Memory
{
    Tracker* Tracker::getSingleton()
    {
        if (!s_singleton.get())
            s_singleton = std::make_unique<Tracker>();

        return s_singleton.get();
    }

    void Tracker::recordAlloc(size_t allocSize) noexcept
    {
        m_currMemUsage += allocSize;
        m_totMemUsage += allocSize;

        m_maxMemUsage = m_currMemUsage > m_maxMemUsage
                        ? m_currMemUsage
                        : m_maxMemUsage;
    }

    void Tracker::recordDealloc(size_t deallocSize) noexcept
    {
        if (deallocSize > m_currMemUsage)
        {
            // TODO: Report or print
            deallocSize = m_currMemUsage;
            ACORN_ASSERT(false && "Deallocated too much memory");
        }

        m_currMemUsage -= deallocSize;
    }

    size_t Tracker::getCurrMemUsage() const noexcept
    {
        return m_currMemUsage;
    }

    size_t Tracker::getTotMemUsage() const noexcept
    {
        return m_totMemUsage;
    }

    size_t Tracker::getMaxMemUsage() const noexcept
    {
        return m_maxMemUsage;
    }
}
