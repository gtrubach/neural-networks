#include "KMeans.h"
#include <chrono>


unsigned int KMeans::getRngSeed() const
{
    return (unsigned int)std::chrono::high_resolution_clock::now()
        .time_since_epoch()
        .count();
}

void KMeans::free(KMeans::Matrix::iterator begin, KMeans::Matrix::iterator end, double value)
{
    for (auto it = begin; it != end; ++it)
    {
        std::fill(it->begin(), it->end(), value);
    }
}

double KMeans::calculateDistance(const Vector& first, const Vector& second)
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

size_t KMeans::chooseCluster(const Matrix& centroids, const Vector& point)
{
    auto minIt = centroids.begin();
    double minDistance = std::numeric_limits<double>::max();
    for (auto it = centroids.begin(); it != centroids.end(); ++it)
    {
        Vector centroid = *it;
        double distance = calculateDistance(point, centroid);
        if (distance < minDistance)
        {
            minDistance = distance;
            minIt = it;
        }
    }
    return minIt - centroids.begin();
}

KMeans::Matrix KMeans::initCentroids(const Matrix& dataset)
{
    Matrix sample = dataset;
    size_t datasetSize = dataset.size();
    auto begin = sample.begin();
    for (size_t i = 0; i < clustersCount; i++)
    {
        auto it = begin + rng() % datasetSize - i;
        std::swap(*begin, *it);
        begin++;
    }
    return Matrix(begin, begin + clustersCount);
}

KMeans::ComputeResult KMeans::computeCore(const Matrix& dataset, const size_t& setSize, const size_t& pointSize)
{
    size_t iteration = 0;
    bool converges = false;
    std::vector<size_t> clustersLabels(setSize);
    std::vector<size_t> clustersSizes(clustersCount);

    Matrix centroids = initCentroids(dataset);
    Matrix newCentroids(clustersCount, Vector(pointSize));
    while (!converges && iteration < maxIterations)
    {
        std::fill(clustersSizes.begin(), clustersSizes.end(), 0);
        free(newCentroids.begin(), newCentroids.end(), 0);
        for (size_t i = 0; i < setSize; i++)
        {
            const Vector& point = dataset[i];
            size_t clusterNumber = chooseCluster(centroids, point);

            clustersLabels[i] = clusterNumber;
            ++clustersSizes[clusterNumber];

            Vector& newCentroid = newCentroids[clusterNumber];
            for (size_t j = 0; j < pointSize; j++)
            {
                newCentroid[j] += point[j];
            }
        }
        converges = true;
        for (size_t i = 0; i < clustersCount; i++)
        {
            Vector& newCentroid = newCentroids[i];
            Vector& currentCentroid = centroids[i];
            size_t clusterSize = clustersSizes[i];
            for (size_t j = 0; j < pointSize; j++)
            {
                double coordinate = newCentroid[j] /= clusterSize;
                if (coordinate != currentCentroid[j])
                {
                    converges = false;
                };
                currentCentroid[j] = coordinate;
            }
        }
        ++iteration;
    }
    return ComputeResult(clustersLabels, centroids);
}

KMeans::KMeans(const size_t& k, const size_t& maxIterations)
    : clustersCount(k), maxIterations(maxIterations), rng(getRngSeed())
{
}

KMeans::ComputeResult KMeans::compute(const std::vector<std::vector<double>>& dataset)
{
    size_t setSize = dataset.size();
    if (dataset.size() < clustersCount)
    {
        throw std::invalid_argument("Set size should be not less than number of clusters.");
    }
    size_t dataSize = dataset.begin()->size();
    for (const Vector& data : dataset)
    {
        if (dataSize != data.size())
        {
            throw std::invalid_argument("Data length in set must be the same.");
        }
    }
    return computeCore(dataset, setSize, dataSize);
}

KMeans::ComputeResult::ComputeResult(const std::vector<size_t>& labels, const std::vector<std::vector<double>>& centroids)
    : labels(labels), centroids(centroids)
{
}