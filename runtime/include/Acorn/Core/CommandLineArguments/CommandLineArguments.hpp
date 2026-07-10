#ifndef ACORN_COMMAND_LINE_ARGUMENTS_HPP
#define ACORN_COMMAND_LINE_ARGUMENTS_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/DetailedError.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Core/CommandLineArguments/CommandLineArgumentsDescriptor.hpp"
#include "Acorn/Templates/String.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/Pair.hpp"

namespace Acorn::Core
{
    class ENGINE_API CommandLineArgumentParseError final :
        public Base::DetailedError
    {
    public:
        CommandLineArgumentParseError(String msg);
    };

    using Key   = String;
    using Value = String;

    class ENGINE_API CommandLineArguments
    {
        public:
            CommandLineArguments(CommandLineArgumentsDescriptor desc);

            const String* getArgument(String argName) const;
            String        getArgumentOr(String argName,
                                        String defaultVal) const;
            bool          hasFlag(String flagName) const;
        
        private:
            void parse(const int argc, char** argv);
            void parseArgument(char* arg);

            Base::Logger m_logger;

            ArrayList<Pair<Key, Value>> m_arguments;
            ArrayList<String> m_flags;
    };
}

#endif /* COMMAND_LINE_ARGUMENTS_HPP */
