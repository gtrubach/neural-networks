#pragma once

#include "Layer.h"
#include "TrainConfig.h"
#include "TrainingSample.h"
#include <vector>

class MLP
{
private:
    std::vector<Layer> layers;
    size_t layersCount;

    double sigmoid(const double& value) const;
    double sigmoidDerivative(const double& value) const;
public:
    MLP(std::vector<size_t> layerSizes);

    void train(const std::vector<TrainingSample>& trainingSet, TrainConfig config);
    void recognise(const std::vector<double>& input) const;
};