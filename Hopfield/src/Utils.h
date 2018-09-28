#pragma once

#include <vector>
#include "Generator.h"

class Utils
{
private:
    using unsignedVectorIt = std::vector<size_t>::iterator;

    static Generator generator;

    static void negate(std::vector<short>& collection, unsignedVectorIt firstIndex, unsignedVectorIt lastIndex);
    static short getNeuronState(const char& c);
    static char getNeuronChar(const short& state);
public:
    static std::vector<short> generateNoisyPattern(const std::vector<short>& pattern, size_t shufflePercent);
    static std::vector<short> readSet(const char* fileName);
    static void writeSet(std::ostream& out, const size_t& size, const std::vector<short>& vector);
};
