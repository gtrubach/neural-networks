#pragma once

#include <vector>
#include <random>

class CompetitiveNetwork
{
private:
    size_t inputSize;
    size_t outputSize;
    std::vector<std::vector<double>> weights;
    std::vector<int> wins;

    std::default_random_engine rng;

    unsigned int getRngSeed() const;
    std::vector<size_t> getTrainOrder(const size_t& setSize) const;
    size_t getWinner(const std::vector<double>& input) const;
public:
    struct TrainParams
    {
        double speed;
        double maxDistance;
        size_t maxIteration;
    };

    CompetitiveNetwork(const size_t& inputSize, const size_t& outputSize);

    void train(const std::vector<std::vector<double>>& dataset, const TrainParams& params);
    size_t predict(const std::vector<double>& input) const;
};