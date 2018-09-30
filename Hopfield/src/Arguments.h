#pragma once

#include <string>
#include <vector>

struct Arguments
{
public:
    size_t patternSize;
    std::vector<std::string> inputs;
    std::string outputDir;
};

class ArgumentsBuilder
{
public:
    static Arguments fromCmd(int argc, char* argv[]);
};

