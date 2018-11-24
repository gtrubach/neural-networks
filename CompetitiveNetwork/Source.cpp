#include <iostream>
#include <fstream>
#include "libs/nlohmann/json.hpp"
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

void drawImage(const vect &in)
{
    int counter = 0;
    for (auto e : in)
    {
        char output = e == 0.0 ? '-' : '*';
        std::cout << output;
        if (++counter % 6 == 0) std::cout << '\n';
    }
}

void readData(const char* path, matr &trainData, size_t &clusters)
{
    clusters = 0;
    nlohmann::json j;
    std::ifstream in(path);
    in >> j;
    in.close();
    for (const auto& obj : j)
    {
        clusters++;
        matr data = obj["Data"];
        trainData.insert(trainData.end(), data.begin(), data.end());
    }
}

void normalizeSet(matr::iterator begin, matr::iterator end, const size_t &n)
{
    for (auto it = begin; it != end; ++it)
    {
        auto &x = *it;
        double len = length(x);
        for (size_t i = 0; i < n; i++)
        {
            x[i] /= len;
        }
    }
}

int main()
{
    size_t n = 36, m;
    matr trainData;
    readData("data/traindata.json", trainData, m);

    normalizeSet(trainData.begin(), trainData.end(), n);

    CompetitiveNetwork::TrainParams trainParams;
    trainParams.speed = 0.01;
    trainParams.maxDistance = 0.01;
    trainParams.maxIteration = 1000;

    CompetitiveNetwork network(n, m);
    network.train(trainData, trainParams);

    for (const auto& x : trainData)
    {
        drawImage(x);
        size_t cluster = network.predict(x);
        std::cout << cluster << '\n';
    }

    size_t testCount;
    matr testData;
    readData("data/testdata.json", testData, testCount);
    normalizeSet(testData.begin(), testData.end(), n);

    for (const auto& x : testData)
    {
        drawImage(x);
        size_t cluster = network.predict(x);
        std::cout << cluster << '\n';
    }

    return 0;
}