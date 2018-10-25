#pragma once

#include <vector>

struct MLPInfo
{
    std::vector<size_t> layerSizes;
    size_t outputTrainSpeed;
    size_t hiddenTrainSpeed;
};