#include "Utils.h"
#include <algorithm>
#include <random>

std::vector<size_t> generateShuffledSequence(const size_t &patternSize);
void negate(std::vector<short>& collection, std::vector<size_t>::iterator firstIndex, std::vector<size_t>::iterator lastIndex);

std::vector<short> generateNoisyPattern(const std::vector<short>& pattern, size_t shufflePercent)
{
    size_t patternSize = pattern.size();
    size_t negateCount = patternSize * shufflePercent / 100;
    std::vector<short> inverted = pattern;
    std::vector<size_t> idxs = generateShuffledSequence(patternSize);
    negate(inverted, idxs.begin(), idxs.begin() + negateCount);
    return inverted;
}

std::vector<size_t> generateShuffledSequence(const size_t &patternSize)
{
    std::vector<size_t> idxs(patternSize);
    for (size_t i = 0; i < patternSize; i++)
    {
        idxs[i] = i;
    }
    auto rng = std::default_random_engine();
    std::shuffle(idxs.begin(), idxs.end(), rng);
    return idxs;
}

void negate(std::vector<short>& collection, std::vector<size_t>::iterator firstIndex, std::vector<size_t>::iterator lastIndex)
{
    for (auto it = firstIndex; it < lastIndex; it++)
    {
        auto idx = *it;
        collection[idx] = -collection[idx];
    }
}
