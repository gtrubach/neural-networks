#include "Hopfield.h"

using vector = std::vector<short>;

short HopfieldNetwork::sign(const int& x) const
{
    return x >= 0 ? 1 : -1;
}

int HopfieldNetwork::multiplyVectors(const vector& first, const vector& second) const
{
    int result = 0;
    for (size_t i = 0; i < neuronsCount; i++)
    {
        result += first[i] * second[i];
    }
    return result;
}

bool HopfieldNetwork::compareVectors(const vector& first, const vector& second) const
{
    size_t size = first.size();
    if (size != second.size())
    {
        return false;
    }
    for (size_t i = 0; i < size; i++)
    {
        if (first[i] != second[i])
        {
            return false;
        }
    }
    return true;
}

void HopfieldNetwork::validateSet(const std::vector<short>& set) const
{
    if (neuronsCount != set.size())
    {
        throw new std::exception("Neurons count and set count does not match.");
    }
}

HopfieldNetwork::HopfieldNetwork(size_t neuronsCount) :
    neuronsCount(neuronsCount),
    weights(matrix(neuronsCount, vector(neuronsCount, 0)))
{
}

void HopfieldNetwork::train(const vector& trainingSet)
{
    if (neuronsCount != trainingSet.size())
    {
        throw new std::exception("Neurons count and set count does not match.");
    }
    for (size_t i = 0; i < neuronsCount; i++)
    {
        for (size_t j = 0; j < neuronsCount; j++)
        {
            if (i == j) weights[i][j] = 0;
            else weights[i][j] += trainingSet[i] * trainingSet[j];
        }
    }
}

vector HopfieldNetwork::recogniseSync(const vector& set) const
{
    validateSet(set);
    bool stabilized = false;
    vector calculatedNeurons = set;
    vector previousNeurons = set;
    while (!stabilized)
    {
        for (size_t i = 0; i < neuronsCount; i++)
        {
            calculatedNeurons[i] = sign(multiplyVectors(weights[i], previousNeurons));
        }
        stabilized = compareVectors(previousNeurons, calculatedNeurons);
        previousNeurons = calculatedNeurons;
    }
    return calculatedNeurons;
}

vector HopfieldNetwork::recogniseAsync(const vector& set) const
{
    validateSet(set);
    bool stabilized = false;
    vector calculatedNeurons = set;
    vector previousNeurons = set;
    while (!stabilized)
    {
        auto idxs = generator.generateShuffledSequence(neuronsCount);
        for (auto i : idxs)
        {
            calculatedNeurons[i] = sign(multiplyVectors(weights[i], calculatedNeurons));
        }
        stabilized = compareVectors(previousNeurons, calculatedNeurons);
        previousNeurons = calculatedNeurons;
    }
    return calculatedNeurons;
}
