#pragma once

#include <vector>

enum class LayerType
{
    Inner,
    Hidden,
    Output
};

class Layer
{
private:
    std::vector<double> neurons;
    std::vector<double> thresholds;
    size_t size;
    LayerType type;
public:
    Layer(const LayerType& type, const size_t& size);

    std::vector<double> getNeurons() const;
    size_t getSize() const;
    LayerType getType() const;
};