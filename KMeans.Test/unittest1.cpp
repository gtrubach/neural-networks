#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KMeansTest
{
    TEST_CLASS(KMeansTest)
    {
    private:
        double distance(const std::vector<double>& first, const std::vector<double>& second)
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
    public:
        TEST_METHOD(TestClustering)
        {
            std::vector<std::vector<double>> dataset = { {1.0, 5.0}, {7.0, 4.0}, {5.0, 2.0}, {7.0, 5.0}, {4.0, 7.0} };
            size_t setSize = dataset.size();

            size_t k = 2;
            KMeans kMeans(k, 10);
            auto result = kMeans.compute(dataset);

            Assert::IsTrue(result.labels.size() == setSize,
                L"Labels count should be the same as set size.");
            Assert::IsTrue(result.centroids.size() == k,
                L"Count of centroids and clusters should be the same.");
            for (size_t i = 0; i < setSize; i++)
            {
                const auto& point = dataset[i];
                size_t clusterLabel = result.labels[i];
                double observedMinDist = distance(point, result.centroids[clusterLabel]);
                for (size_t j = 0; j < k; j++)
                {
                    Assert::IsTrue(observedMinDist <= distance(point, result.centroids[j]),
                        L"Distance in point cluster should be minimal.");
                }
            }
        }

        TEST_METHOD(TestClustersCountCheck)
        {
            std::vector<std::vector<double>> dataset = { {1.0, 5.0}, {7.0, 4.0} };

            KMeans kMeans(3, 10);

            Assert::ExpectException<std::invalid_argument>([kMeans, dataset]
            {
                return const_cast<KMeans&>(kMeans).compute(dataset);
            }, L"Exception should be thrown when clusters count is more than set size.");
        }

        TEST_METHOD(TestPointsSizeCheck)
        {
            std::vector<std::vector<double>> dataset = { {1.0, 5.0}, {7.0, 4.0, 3.0} };

            KMeans kMeans(2, 10);

            Assert::ExpectException<std::invalid_argument>([kMeans, dataset]
            {
                return const_cast<KMeans&>(kMeans).compute(dataset);
            }, L"Exception should be thrown when input matrix is not square.");
        }
    };
}