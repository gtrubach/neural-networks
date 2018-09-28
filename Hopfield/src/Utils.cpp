#include <fstream>
#include "Generator.h"
#include "Utils.h"

Generator Utils::generator;

void Utils::negate(std::vector<short>& collection, unsignedVectorIt firstIndex, unsignedVectorIt lastIndex)
{
    for (auto it = firstIndex; it < lastIndex; it++)
    {
        auto idx = *it;
        collection[idx] = -collection[idx];
    }
}

short Utils::getNeuronState(const char & c)
{
    short state;
    switch (c)
    {
    case '-':
        state = -1;
        break;
    case '*':
        state = 1;
        break;
    default:
        throw new std::exception("Invalid pattern character. Only - and * are allowed.");
    }
    return state;
}

char Utils::getNeuronChar(const short & state)
{
    switch (state)
    {
    case -1:
        return '-';
    case 1:
        return '*';
    default:
        throw new std::exception("Invalid state. Only -1 and 1 are allowed.");
    }
}

std::vector<short> Utils::generateNoisyPattern(const std::vector<short>& pattern, size_t shufflePercent)
{
    size_t patternSize = pattern.size();
    size_t negateCount = patternSize * shufflePercent / 100;
    std::vector<short> inverted = pattern;
    std::vector<size_t> idxs = generator.generateShuffledSequence(patternSize);
    negate(inverted, idxs.begin(), idxs.begin() + negateCount);
    return inverted;
}

std::vector<short> Utils::readSet(const char * fileName)
{
    std::ifstream infile(fileName);
    if (!infile)
    {
        throw new std::exception("There are problems with reading file.");
    }
    std::vector<short> trainingSet;
    char c;
    while (infile.get(c))
    {
        if (c != '\n')
        {
            short state = getNeuronState(c);
            trainingSet.push_back(state);
        }
    }
    return trainingSet;
}

void Utils::writeSet(std::ostream & out, const size_t& size, const std::vector<short>& vector)
{
    size_t j = 0;
    for (auto i : vector)
    {
        out << getNeuronChar(i) << ' ';
        if (!(++j % size))
        {
            out << '\n';
        }
    }
    out << '\n';
}
