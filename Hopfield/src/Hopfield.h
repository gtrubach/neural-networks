#pragma once

#include <vector>
#include "Generator.h"

class HopfieldNetwork
{
private:
    using matrix = std::vector<std::vector<short>>;

    size_t neuronsCount;
    matrix weights;
    Generator generator;

    short sign(const int& x) const;
    int multiplyVectors(const std::vector<short>& first, const std::vector<short>& second) const;
    bool compareVectors(const std::vector<short>& first, const std::vector<short>& second) const;
    void validateSet(const std::vector<short>& set) const;
public:
    HopfieldNetwork(size_t neuronsCount);

    void train(const std::vector<short>& trainingSet);
    std::vector<short> recogniseSync(const std::vector<short>& set) const;
    std::vector<short> recogniseAsync(const std::vector<short>& set) const;
};
