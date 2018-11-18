#include <iostream>
#include "CompetitiveNetwork.h"

using vect = std::vector<double>;
using matr = std::vector<std::vector<double>>;

double length(const vect& v)
{
    double result = 0.0;
    for (auto& coordinate : v)
    {
        result += coordinate * coordinate;
    }
    return sqrt(result);
}

void DrawImage(const vect &in)
{
    int counter = 0;
    for (auto e : in)
    {
        char output = e == 0.0 ? '-' : '*';
        std::cout << output;
        if (++counter % 6 == 0) std::cout << '\n';
    }
}

int main()
{
    size_t n = 36, m = 5;

    matr inputs =
    {
        // ^
        {
            0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
            1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        },
        // ˅
        {
            1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        },
        // ꓱ
        {
            1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        },
        // ⊂
        {
            0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        },
        // ⊃
        {
            1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        }
    };

    matr normedInputs = inputs;
    for (vect& x : normedInputs)
    {
        double len = length(x);
        for (size_t i = 0; i < n; i++)
        {
            x[i] /= len;
        }
    }

    CompetitiveNetwork::TrainParams trainParams;
    trainParams.speed = 0.01;
    trainParams.maxDistance = 0.01;
    trainParams.maxIteration = 1000;

    CompetitiveNetwork network(n, m);
    network.train(normedInputs, trainParams);

    for (const auto& x : normedInputs)
    {
        DrawImage(x);
        size_t cluster = network.predict(x);
        std::cout << cluster << '\n';
    }

    return 0;
}