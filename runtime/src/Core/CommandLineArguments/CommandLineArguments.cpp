#include "Acorn/Core/CommandLineArguments/CommandLineArguments.hpp"
#include "Acorn/Base/Assert.hpp"
#include "Acorn/Base/Format.hpp"

namespace Acorn::Core
{
    CommandLineArgumentParseError::CommandLineArgumentParseError(String msg)
        : Base::DetailedError("CommandLineArgumentParseError", std::move(msg))
    {}

    /* Should I give every command line arguments instance a 
     * unique logger name ??
     * There is only supposed to be one but this is never gonna be a 
     * singleton anyway so...
     */
    CommandLineArguments::CommandLineArguments(
        CommandLineArgumentsDescriptor desc)
        : m_logger(desc.factory.create("CommandLineArguments"))
    {
        parse(desc.argc, desc.argv);
    }

    const String* CommandLineArguments::getArgument(String argName) const
    {
        for (const auto& pair: m_arguments)
        {
            if (pair.m_first == argName)
                return &pair.m_second;
        }

        return nullptr;
    }

    String CommandLineArguments::getArgumentOr(String argName,
                                               String defaultVal) const
    {
        const String* arg = getArgument(std::move(argName));
        return arg ? *arg : std::move(defaultVal);
    }

    bool CommandLineArguments::hasFlag(String flagName) const
    {
        for (const auto& flag: m_flags)
        {
            if (flag == flagName)
                return true;
        }

        return false;
    }

    void CommandLineArguments::parse(const int argc, char** argv)
    {
        constexpr bool skipFirst = true;

        for (int i = skipFirst ? 1 : 0; i < argc; ++i)
        {
            try
            {
                parseArgument(argv[i]);
            }
            catch (const Base::DetailedError& err)
            {
                m_logger.warn("Invalid command line argument: {}", err.what());
            }
        }
    }

    void CommandLineArguments::parseArgument(char* arg)
    {
        size_t charIndex{0};
        bool isArgValid{false};
        bool isFlag{true};
        String argName{""};
        String argValue{};

        ACORN_ASSERT(arg);

        while (arg[charIndex] != '\0')
        {
            if (charIndex < 2)
            {
                if (arg[charIndex] != '-')
                    throw CommandLineArgumentParseError(
                        "Doesn't start with '--'");
            }
            else if (arg[charIndex] == '=')
            {
                isFlag = false;
                isArgValid = false;
            }
            else if (arg[charIndex] == '-' || std::isalnum(arg[charIndex]))
            {
                if (isFlag && !isArgValid && !std::isalpha(arg[charIndex]))
                {
                    // It's the first character of the parameter name and it's
                    // not a letter: invalid name
                    throw CommandLineArgumentParseError(
                        "Name doesn't start with a letter");
                }

                if (isFlag)
                    argName.append(arg[charIndex]);
                else
                    argValue.append(arg[charIndex]);

                isArgValid = true;
            }
            else
            {
                throw CommandLineArgumentParseError(Base::format(
                    "Unexpected character: '{}'",
                    arg[charIndex]
                ));
            }

            charIndex++;
        }

        if (!isArgValid)
        {
            throw CommandLineArgumentParseError(
                "Invalid command line argument or flag");
        }

        if (isFlag)
            m_flags.append(argName);
        else
        {
            bool replaced = false;
            for (auto& [name, value]: m_arguments)
            {
                if (name == argName)
                {
                    value = argValue;
                    replaced = true;
                }
            }

            if (!replaced)
            {
                m_arguments.append({argName, argValue});
            }
        }
    }
}
