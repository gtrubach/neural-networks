#include "Utils.h"
#include <algorithm>
#include <random>

std::vector<size_t> generateShuffledSequence(const size_t &patternSize);
void negate(std::vector<short>::iterator first, std::vector<short>::iterator last);

std::vector<short> generateNoisyPattern(const std::vector<short>& pattern, size_t shufflePercent)
{
    size_t patternSize = pattern.size();

    generateShuffledSequence(patternSize);

    std::vector<short> inverted = pattern;

    size_t negateCount = patternSize * shufflePercent / 100;
    negate(inverted.begin(), inverted.begin() + negateCount);

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

void negate(std::vector<short>::iterator first, std::vector<short>::iterator last)
{
    for (auto it = first; it < last; it++)
    {
        *it = -(*it);
    }
}
