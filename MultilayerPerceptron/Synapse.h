#pragma once

#include "Layer.h"
#include <vector>

class Synapse
{
private:
    using Matrix = std::vector<std::vector<double>>;

    //Layer firstLayer;
    //Layer secondLayer;
    Matrix weights;
public:
    Synapse();
    ~Synapse();
};

