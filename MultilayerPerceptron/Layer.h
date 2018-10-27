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
    std::vector<std::vector<double>> weights;
    size_t size;
    LayerType type;
    
public:
    std::vector<double> neurons;
    std::vector<double> thresholds;

    Layer(const LayerType& type, const size_t& size);

    std::vector<double> getNeurons() const;
    size_t getSize() const;
    LayerType getType() const;

    void prepare(const size_t &synapsesCount);
};