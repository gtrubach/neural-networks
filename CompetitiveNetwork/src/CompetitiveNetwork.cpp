#include "CompetitiveNetwork.h"
#include <chrono>


unsigned int CompetitiveNetwork::getRngSeed() const
{
    return (unsigned int)std::chrono::high_resolution_clock::now()
        .time_since_epoch()
        .count();
}

std::vector<size_t> CompetitiveNetwork::getTrainOrder(const size_t& setSize) const
{
    std::vector<size_t> trainOrder;
    trainOrder.reserve(setSize);
    for (size_t i = 0; i < setSize; i++)
    {
        trainOrder.push_back(i);
    }
    return trainOrder;
}

size_t CompetitiveNetwork::getWinner(const std::vector<double>& input) const
{
    double minDistortion = std::numeric_limits<double>::max();
    size_t winner = 0;
    for (size_t j = 0; j < outputSize; j++)
    {
        double distance = 0.0;
        for (int i = 0; i < inputSize; i++)
        {
            double tmp = input[i] - weights[i][j];
            distance += tmp * tmp;
        }
        distance = sqrt(distance);
        double distortion = distance * wins[j];
        if (distortion < minDistortion)
        {
            minDistortion = distortion;
            winner = j;
        }
    }
    return winner;
}

CompetitiveNetwork::CompetitiveNetwork(const size_t& inputSize, const size_t& outputSize)
    : inputSize(inputSize),
    outputSize(outputSize),
    weights(inputSize, std::vector<double>(outputSize)),
    wins(outputSize),
    rng(getRngSeed())
{
    std::uniform_real_distribution<double> distr(0.0, 1.0);
    for (size_t j = 0; j < outputSize; j++)
    {
        double len = 0.0;
        for (size_t i = 0; i < inputSize; i++)
        {
            double tmp = distr(rng);
            weights[i][j] = tmp;
            len += tmp * tmp;
        }
        len = sqrt(len);
        for (size_t i = 0; i < inputSize; i++)
        {
            weights[i][j] /= len;
        }
    }
}

void CompetitiveNetwork::train(const std::vector<std::vector<double>>& dataset, const TrainParams& params)
{
    for (const auto& data : dataset)
    {
        if (data.size() != inputSize)
        {
            throw std::invalid_argument("Wrong input size.");
        }
    }
    std::vector<size_t> trainOrder = getTrainOrder(dataset.size());
    size_t iteration = 0;
    double converges = false;
    while (!converges)
    {
        std::shuffle(trainOrder.begin(), trainOrder.end(), rng);
        double maxDistance = 0.0;
        for (size_t dataIdx : trainOrder)
        {
            const auto& data = dataset[dataIdx];
            size_t winner = getWinner(data);
            wins[winner]++;
            double len = 0.0;
            for (size_t i = 0; i < inputSize; i++)
            {
                weights[i][winner] += params.speed * (data[i] - weights[i][winner]);
                len += weights[i][winner] * weights[i][winner];
            }
            len = sqrt(len);
            double distance = 0.0;
            for (size_t i = 0; i < outputSize; i++)
            {
                double tmp = weights[i][winner] / len;
                weights[i][winner] = tmp;
                distance += tmp * tmp;
            }
            distance = sqrt(distance);
            if (maxDistance < distance)
            {
                maxDistance = distance;
            }
        }
        converges = maxDistance <= params.maxDistance || ++iteration >= params.maxIteration;
    }
}

size_t CompetitiveNetwork::predict(const std::vector<double>& input) const
{
    if (input.size() != inputSize)
    {
        throw std::invalid_argument("Wrong input size.");
    }
    return getWinner(input);
}