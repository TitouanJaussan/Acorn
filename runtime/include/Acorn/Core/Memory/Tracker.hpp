#ifndef ACORN_MEMORY_TRACKER_HPP
#define ACORN_MEMORY_TRACKER_HPP

#include <memory>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Memory
{
    class ENGINE_API Tracker
    {
    public:
        Tracker() = default;

        static Tracker* getSingleton();

        void recordAlloc(size_t allocSize) noexcept;
        void recordDealloc(size_t deallocSize) noexcept;

        size_t getCurMemUsage() const noexcept;
        size_t getTotMemUsage() const noexcept;
        size_t getMaxMemUsage() const noexcept;
    
    private:
        inline static std::unique_ptr<Tracker> s_singleton;

        size_t m_currMemUsage{0};
        size_t m_totMemUsage{0};
        size_t m_maxMemUsage{0};
    };
}

#endif /* ACORN_MEMORY_TRACKER_HPP */
