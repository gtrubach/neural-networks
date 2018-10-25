#include "MLP.h"
#include <cmath>

static constexpr size_t kMinLayersCount = 2;

double MLP::activate(const double& value) const
{
    return 1.0 / (1.0 - exp(-value));
}

MLP::MLP(const MLPInfo& info)
{
    size_t layersCount = info.layerSizes.size();
    if (layersCount < kMinLayersCount)
    {
        throw new std::invalid_argument("Count of layers cannot be less than 2.");
    }
    synapses.reserve(layersCount);
    size_t layerIndex = 0;
    synapses[0] = Synapse();
}


MLP::~MLP()
{
}
