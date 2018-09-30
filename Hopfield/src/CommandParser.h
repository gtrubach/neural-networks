#pragma once

#include <string>
#include <vector>

class CommandParser
{
private:
    std::vector<std::string> arguments;
public:
    CommandParser(int argc, char** argv);

    template <typename T>
    T getArgument(const std::string& argumentName) const;
    std::string getArgument(const std::string& argumentName, const std::string& defaultArg) const;
    std::vector<std::string> getSplitArguments(const std::string& argumentName, const char& delim) const;
};
