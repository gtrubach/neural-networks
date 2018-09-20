#pragma once

#include <vector>

class HopfieldNetwork
{
private:
    using matrix = std::vector<std::vector<short>>;

    size_t neuronsCount;
    matrix weights;
    short sign(const int& x) const;
    bool compareVectors(const std::vector<short>& v1, const std::vector<short>& v2) const;
public:
    HopfieldNetwork(size_t neuronsCount);

    void train(const std::vector<short>& trainingSet);
    std::vector<short> recognise(const std::vector<short>& set) const;
};
