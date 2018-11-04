#include "KMeans.h"

double KMeans::distance(const Point& first, const Point& second)
{
    double dist = 0.0;
    auto firstIt = first.begin();
    auto secondIt = second.begin();
    for (; firstIt != first.end(); ++firstIt, ++secondIt)
    {
        double localDist = *firstIt - *secondIt;
        dist += localDist * localDist;
    }
    return sqrt(dist);
}

size_t KMeans::indexOfMinimum(const Point& data)
{
    auto minIdx = data.begin();
    double minElement = *minIdx;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        double element = *it;
        if (element < minElement)
        {
            minElement = element;
            minIdx = it;
        }
    }
    return minIdx - data.begin();
}

Center KMeans::calculateCenter(const Cluster& cluster, const size_t& dataSize)
{
    Center center(dataSize);
    for(double coordinate: center)
    {
        for (auto point : cluster)
        {
            coordinate += point[i];
        }
        coordinate /= clustersCount;
    }
    return center;
}


KMeans::KMeans(const size_t& k, const size_t& maxIterations)
    : clustersCount(k), maxIterations(maxIterations)
{
}

void KMeans::compute(const Dataset& dataset)
{
    if (dataset.getSetSize() < clustersCount)
    {
        throw new std::invalid_argument("Set size should be not less than number of clusters.");
    }

    size_t dataSize = dataset.getDataSize();
    size_t iteration = 0;
    bool converges = false;

    std::vector<std::vector<std::vector<double>>> clusters;

    //auto seed = (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    //std::default_random_engine rng(seed);
    std::vector<std::vector<double>> centers /*= sample(ds, k,)*/;

    while (!converges && iteration < maxIterations)
    {
        clusters = std::vector<std::vector<std::vector<double>>>(clustersCount);
        for (auto point : dataset)
        {
            std::vector<double> distances;
            distances.reserve(clustersCount);
            for (auto center : centers)
            {
                distances.push_back(distance(point, center));
            }
            size_t clusterNumber = indexOfMinimum(distances);
            clusters[clusterNumber].push_back(point);
        }
        for (size_t i = 0; i < clustersCount; i++)
        {
            std::vector<double> newCenter = calculateCenter(clusters[i], dataSize);
            converges = newCenter == centers[i];
            centers[i] = newCenter;
        }
        iteration++;
    }
}