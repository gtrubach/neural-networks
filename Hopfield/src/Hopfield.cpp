#include "Hopfield.h"

using vector = std::vector<short>;

short HopfieldNetwork::sign(const int& x) const
{
    return x > 0 ? 1 : -1;
}

bool HopfieldNetwork::compareVectors(const vector & v1, const vector & v2) const
{
    size_t size = v1.size();
    if (size != v2.size())
    {
        return false;
    }
    for (size_t i = 0; i < size; i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    return true;
}

HopfieldNetwork::HopfieldNetwork(size_t neuronsCount) :
    neuronsCount(neuronsCount),
    weights(matrix(neuronsCount, vector(neuronsCount)))
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

vector HopfieldNetwork::recognise(const vector& set) const
{
    if (neuronsCount != set.size())
    {
        throw new std::exception("Neurons count and set count does not match.");
    }
    bool stabilized = false;
    vector calculatedNeurons(neuronsCount, 0);
    vector previousNeurons = set;
    while (!stabilized)
    {
        for (size_t i = 0; i < neuronsCount; i++)
        {
            int result = 0;
            for (size_t j = 0; j < neuronsCount; j++)
            {
                result += weights[i][j] * previousNeurons[j];
            }
            calculatedNeurons[i] = sign(result);
        }
        stabilized = compareVectors(previousNeurons, calculatedNeurons);
        previousNeurons = calculatedNeurons;
    }
    return calculatedNeurons;
}
