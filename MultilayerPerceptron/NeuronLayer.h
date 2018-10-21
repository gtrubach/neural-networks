#pragma once

#include <vector>

struct NeuronLayer
{
private:
    std::vector<double> neurons;
    size_t count;
public:
    NeuronLayer();
    ~NeuronLayer();
};

