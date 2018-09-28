#pragma once

#include <vector>
#include <random>

class Generator
{
private:
    std::unique_ptr<std::default_random_engine> pRng;

    static std::default_random_engine* initRandomEngine();
public:
    Generator();

    std::vector<size_t> generateShuffledSequence(const size_t& size) const;
};
