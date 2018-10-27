#pragma once

#include <vector>
#include <memory>

enum class LayerType
{
    Inner,
    Hidden,
    Output
};

class Layer
{
private:
    std::vector<double> thresholds;
    std::vector<std::vector<double>> weights;
    size_t size;
    LayerType type;
    std::unique_ptr<Layer> previous;
public:
    std::vector<double> neurons;

    Layer(const LayerType& type, const size_t& size, Layer* previousLayer);

    std::vector<double> getNeurons() const;
    size_t getSize() const;
    LayerType getType() const;

    void prepare(const size_t &synapsesCount);
    void updateNeurons();
};