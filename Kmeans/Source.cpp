#include <iostream>
#include <vector>
#include "KMeans.h"


int main()
{
    std::vector<std::vector<double>> dataset = { {1.0, 5.0}, {7.0, 4.0}, {5.0, 2.0}, {7.0, 5.0}, {4.0, 7.0} };
    size_t setSize = dataset.size();
    size_t k = 2;

    KMeans kmeans(k, 10);
    auto result = kmeans.compute(dataset);

    for (size_t i = 0; i < k; i++)
    {
        std::cout << "Cluster " << i << '\n';
        std::cout << "Points:\n";
        for (size_t j = 0; j < setSize; j++)
        {
            if (result.labels[j] == i)
            {
                for (double coord : dataset[j])
                {
                    std::cout << coord << ' ';
                }
                std::cout << '\n';
            }
        }
        std::cout << "Centers:\n";
        for (auto center : result.centroids[i])
        {
            std::cout << center << ' ';
        }
        std::cout << "\n==========\n";
    }
}