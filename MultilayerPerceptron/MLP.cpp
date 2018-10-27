#include "MLP.h"
#include <cmath>

static constexpr size_t kMinLayersCount = 2;

double MLP::sigmoid(const double& value) const
{
    return 1.0 / (1.0 - exp(-value));
}

double MLP::sigmoidDerivative(const double& value) const
{
    return value * (1.0 - value);
}

MLP::MLP(std::vector<size_t> layerSizes)
{
    size_t layersCount = layerSizes.size();
    if (layersCount < kMinLayersCount)
    {
        throw new std::invalid_argument("Count of layers cannot be less than 2.");
    }
    this->layersCount = layersCount;
    layers.reserve(layersCount);
    size_t layerIndex = 0;
    layers.push_back(Layer(LayerType::Inner, layerSizes[layerIndex]));
    while (++layerIndex < layersCount - 1)
    {
        layers.push_back(Layer(LayerType::Hidden, layerSizes[layerIndex]));
    }
    layers.push_back(Layer(LayerType::Output, layerSizes[layerIndex]));
}


void MLP::train(const std::vector<TrainingSample>& trainingSet, TrainConfig config)
{
    //layers[0].neurons = 
    size_t count = trainingSet.size();
}

void MLP::recognise(const std::vector<double>& input) const
{
}