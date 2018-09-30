#include <algorithm>
#include <sstream>
#include "CommandParser.h"

CommandParser::CommandParser(int argc, char** argv) : arguments(argc)
{
    for (int i = 1; i < argc; i++)
    {
        arguments[i - 1] = std::string(argv[i]);
    }
}

template <>
std::string CommandParser::getArgument(const std::string& argumentName) const
{
    auto arg = getArgument(argumentName, {});
    if(arg.empty())
        throw std::exception("Wrong paramter!");
    return arg;
}

template <>
size_t CommandParser::getArgument(const std::string& argumentName) const
{
    auto arg = getArgument<std::string>(argumentName);
    return std::stoul(arg);
}

std::string CommandParser::getArgument(const std::string& argumentName, const std::string& defaultArg) const
{
    auto it = std::find(arguments.begin(), arguments.end(), argumentName);
    if (it == arguments.end() || ++it == arguments.end())
        return defaultArg;
    return *it;
}

std::vector<std::string> CommandParser::getSplitArguments(const std::string & argumentName, const char & delim) const
{
    std::vector<std::string> args;
    std::stringstream ss(getArgument<std::string>(argumentName));
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
        {
            args.push_back(item);
        }
    }
    return args;
}
