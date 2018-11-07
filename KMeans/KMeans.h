#pragma once

#include <vector>
#include <random>

class KMeans
{
public:
    struct ComputeResult
    {
        std::vector<size_t> labels;
        std::vector<std::vector<double>> centroids;

        ComputeResult(const std::vector<size_t>& labels, const std::vector<std::vector<double>>& centroids);
    };
private:
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    struct ComputeResult;

    size_t clustersCount;
    size_t maxIterations;

    std::mt19937 rng;
    unsigned int getRngSeed() const;

    void free(KMeans::Matrix::iterator begin, KMeans::Matrix::iterator end, double value);
    double calculateDistance(const Vector& first, const Vector& second);
    size_t chooseCluster(const Matrix& centroids, const Vector& point);
    Matrix initCentroids(const Matrix& dataset);
    ComputeResult computeCore(const Matrix& dataset, const size_t& setSize, const size_t& pointSize);
public:
    KMeans(const size_t& clusters, const size_t& maxIterations);

    ComputeResult compute(const std::vector<std::vector<double>>& dataset);
};