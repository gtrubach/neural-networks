#pragma once

#include <vector>

class MultilayerPerceptron
{
private:
    std::vector<double> inputNeurons;
    std::vector<double> hiddenNeurons;
    std::vector<double> outputNeurons;

    double activate(const double& value) const;
public:
    MultilayerPerceptron();
    ~MultilayerPerceptron();
};

