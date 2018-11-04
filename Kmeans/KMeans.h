#pragma once

#include <vector>
#include "Dataset.h"

//using Center = std::vector<double>;
//using Centers = std::vector<Center>;
//using Cluster = std::vector<Point>;
//using Clusters = std::vector<Cluster>;

class KMeans
{
private:
    using Point = Dataset::Data;
    using doubleVector = std::vector<double>;
    using doubleMatrix = std::vector<doubleVector>;

    size_t clustersCount;
    size_t maxIterations;

    double distance(const Point& first, const Point& second);
    size_t indexOfMinimum(const Point& data);
    Center calculateCenter(const Cluster& cluster, const size_t& dataSize);
public:
    KMeans(const size_t& clusters, const size_t& maxIterations);
    void compute(const Dataset& dataset);
};