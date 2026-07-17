#ifndef ACORN_RUNTIME_ENGINE_HPP
#define ACORN_RUNTIME_ENGINE_HPP

#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Core/Runtime/CoreState.hpp"
#include "Acorn/Core/Runtime/Systems.hpp"
#include "Acorn/Core/CommandLineArguments/CommandLineArguments.hpp"
#include "Acorn/Core/Runtime/API.hpp"

namespace Acorn::Runtime
{
    class ENGINE_API Engine
    {
    public:
        Engine(int argc, char** argv);
        ~Engine();

        Engine(Engine&&)                 = delete;
        Engine(const Engine&)            = delete;
        Engine& operator=(Engine&&)      = delete;
        Engine& operator=(const Engine&) = delete;

        void run();
        void stop();

        template<Core::LayerT T, typename... Args>
        void pushLayer(Args&&... args);

        Base::LoggerFactory& getLoggerFactory();
        API createAPI();
        Version::Version version() const noexcept;

    private:
        void logEngineInfo();

        Runtime::CoreState m_core;

    public:
        const Core::CommandLineArguments cmdLineArgs;
        Systems systems;
    };
}

#include "Acorn/Core/Runtime/Engine.ipp"

#endif /* ACORN_RUNTIME_ENGINE_HPP */
