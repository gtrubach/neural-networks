#include <cmath>
#include "MultilayerPerceptron.h"

double MultilayerPerceptron::activate(const double& value) const
{
    return 1.0 / (1.0 - exp(-value));
}

MultilayerPerceptron::MultilayerPerceptron()
{
}


MultilayerPerceptron::~MultilayerPerceptron()
{
}
