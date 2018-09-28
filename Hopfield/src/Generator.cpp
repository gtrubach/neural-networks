#include <chrono>
#include "Generator.h"

std::default_random_engine* Generator::initRandomEngine()
{
    auto seed = (size_t)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    return new std::default_random_engine(seed);
}

Generator::Generator() : pRng(initRandomEngine())
{
}

std::vector<size_t> Generator::generateShuffledSequence(const size_t& size) const
{
    std::vector<size_t> idxs(size);
    for (size_t i = 0; i < size; i++)
    {
        idxs[i] = i;
    }
    std::shuffle(idxs.begin(), idxs.end(), *pRng);
    return idxs;
}

