#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <random>
#include <chrono>

#include "KMeans.h"

using data = std::vector<double>;
using center = std::vector<double>;
using distances = std::vector<double>;
using dataset = std::vector<data>;
using centers = std::vector<center>;
using cluster = std::vector<data>;
using clusters = std::vector<cluster>;

//struct Cluster
//{
//    dataset _dataset;
//    center _center;
//};

template<class RNG>
dataset sample(const dataset& _dataset, const size_t& size, RNG &gen)
{
    dataset _sample = _dataset;
    size_t datasetSize = _dataset.size();
    dataset::iterator begin = _sample.begin();
    for (size_t i = 0; i < size; i++)
    {
        auto it = begin + gen() % datasetSize - i;
        std::swap(*begin, *it);
        begin++;
    }
    return dataset(begin, begin + size);
}

double distance(const data& data1, const data& data2)
{
    double dist = 0.0;
    size_t dataSize = data1.size();
    assert(dataSize == data2.size());
    for (size_t i = 0; i < dataSize; i++)
    {
        double localDist = data1[i] - data2[i];
        dist += localDist * localDist;
    }
    return sqrt(dist);
}

size_t indexAtMin(const data& _data)
{
    auto minEl = _data[0];
    auto idx = _data.begin();
    for (auto it = _data.begin(); it != _data.end(); it++)
    {
        auto el = *it;
        if (el < minEl)
        {
            minEl = el;
            idx = it;
        }
    }
    return idx - _data.begin();
}

center calcCenter(const cluster& _cluster)
{
    size_t k = _cluster.size();
    size_t dataSize = _cluster[0].size();
    center _center(dataSize);
    for (size_t i = 0; i < dataSize; i++)
    {
        for (auto _data : _cluster)
        {
            _center[i] += _data[i];
        }
        _center[i] /= k;
    }
    return _center;
}

int main()
{
    dataset ds = { {1.0, 5.0}, {7.0, 4.0}, {5.0, 2.0}, {7.0, 5.0}, {4.0, 7.0} };
    //Dataset dataset = { {1.0, 5.0}, {7.0, 4.0}, {5.0, 2.0}, {7.0, 5.0}, {4.0, 7.0} };
    Dataset dataset = { };
    //Dataset dataset = { {1.0, 5.0}, {7.0, 4.0,3}, {5.0, 2.0}, {7.0, 5.0}, {4.0, 7.0} };
    size_t k = 2;

    KMeans kmeans(k, 10);

    bool converges = false;

    clusters _clusters;

    auto seed = (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    centers cts = sample(ds, k, rng);

    while (!converges)
    {
        _clusters = clusters(k);
        for (auto dt : ds)
        {
            distances dst;
            dst.reserve(k);
            for (auto ct : cts)
            {
                dst.push_back(distance(dt, ct));
            }
            size_t clusterNumber = indexAtMin(dst);
            _clusters[clusterNumber].push_back(dt);
        }
        for (size_t i = 0; i < k; i++)
        {
            center newCenter = calcCenter(_clusters[i]);
            converges = newCenter == cts[i];
            cts[i] = newCenter;
        }
    }
    for (size_t i = 0; i < k; i++)
    {
        std::cout << "Cluster " << i << '\n';
        std::cout << "Data:\n";
        for (auto _data : _clusters[i])
        {
            std::cout << "Point:\n";
            for (auto el : _data)
            {
                std::cout << el << '\n';
            }
        }
        std::cout << "Centers:\n";
        for (auto _center : cts[i])
        {
            std::cout << _center << '\n';
        }
        std::cout << "==========\n";
    }
}