#pragma once

#include "Synapse.h"
#include "MLPInfo.h"
#include <vector>

class MLP
{
private:
    std::vector<Synapse> synapses;

    double activate(const double& value) const;
public:
    MLP(const MLPInfo& info);

    void train();
    void recognise();
};