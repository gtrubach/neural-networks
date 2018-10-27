#pragma once

#include <vector>

struct TrainingSample
{
    std::vector<double> input;
    std::vector<double> output;

    TrainingSample(std::vector<double> input, std::vector<double> output)
        : input(input), output(output)
    {
    }
};