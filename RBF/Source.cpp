#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

#include <KMeans.h>

using namespace std;

using vect = vector<double>;
using matr = vector<vector<double>>;

double activate(double value)
{
    if (value > 1.0)
    {
        return 1.0;
    }
    if (value < -1.0)
    {
        return -1.0;
    }
    return value;
}

double calculateDistance(const vect& first, const vect& second)
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

vect createRandomVector(const size_t& size,
    default_random_engine& rng,
    uniform_real_distribution<double>& distr)
{
    vect res(size);
    for (size_t i = 0; i < size; i++)
    {
        res[i] = distr(rng);
    }
    return res;
}

double maxAbs(matr m)
{
    double tmp = fabs(m[0][0]);

    for (auto row : m)
    {
        for (auto el : row)
        {
            double elAbs = fabs(el);
            if (elAbs > tmp) tmp = elAbs;
        }
    }

    return tmp;
}

void DrawImage(vect &in)
{
    int counter = 0;
    for (auto e : in)
    {
        char output = e == 1.0 ? '*' : '-';
        cout << output;
        if (++counter % 6 == 0) cout << '\n';
    }
}

matr createRandomMatrix(const size_t &n,
    const size_t &h,
    default_random_engine& rng,
    uniform_real_distribution<double>& distr)
{
    matr m(n, vect(h));
    for (size_t i = 0; i < n; i++)
    {
        m[i] = createRandomVector(h, rng, distr);
    }
    return m;
}

int main()
{
    size_t n = 36, h = 2, m = 5, p = 5;

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
    matr outputs =
    {
        { 1.0, 0.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 0.0, 1.0 }
    };

    matr rbfUnits(p, vect(h));
    matr outputsTrained(m, vect(m));

    auto seed = (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution<double> distr(-1.0, 1.0);

    double alpha;
    alpha = 2.0;
    matr wHO = createRandomMatrix(h, m, rng, distr);
    matr ferr(p, vect(m));

    std::clock_t start;
    double duration;

    start = std::clock();

    KMeans kMeans(h, 10);
    auto kMeansResult = kMeans.compute(inputs);
    auto centroids = kMeansResult.centroids;

    vect widths(h);
    for (size_t j = 0; j < h; j++)
    {
        auto& clusterCentroid = centroids[j];
        double minDistance = std::numeric_limits<double>::max();
        for (size_t l = 0; l < h; l++)
        {
            if (j != l)
            {
                double dist = calculateDistance(clusterCentroid, centroids[l]);
                if (dist < minDistance)
                {
                    minDistance = dist;
                }
            }
        }
        widths[j] = minDistance * minDistance / 4.0;
    }

    for (size_t idx = 0; idx < p; idx++)
    {
        vect in = inputs[idx];
        for (size_t j = 0; j < h; j++)
        {
            auto centroid = centroids[j];
            double dist = calculateDistance(in, centroid);
            rbfUnits[idx][j] = exp(-dist / (2 * widths[j] * widths[j]));
        }
    }

    size_t iter = 0;
    do
    {
        for (size_t idx = 0; idx < p; idx++)
        {
            const vect& hid = rbfUnits[idx];
            vect out = outputsTrained[idx];
            vect outReal = outputs[idx];

            for (size_t k = 0; k < m; k++)
            {
                double tmp = 0.0;
                for (size_t j = 0; j < h; j++)
                {
                    tmp += wHO[j][k] * hid[j];
                }
                out[k] = activate(tmp);
            }

            vect err(m);

            for (size_t k = 0; k < m; k++)
            {
                err[k] = outReal[k] - out[k];
                ferr[idx][k] = err[k];
            }

            for (size_t k = 0; k < m; k++)
            {
                for (size_t j = 0; j < h; j++)
                {
                    wHO[j][k] += alpha * err[k] * hid[j];
                }
            }

            outputsTrained[idx] = out;
        }
        iter++;
    } while (maxAbs(ferr) >= 0.0001);

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "=============\n";
    std::cout << "Train stats:\n";
    for (size_t i = 0; i < p; i++)
    {
        DrawImage(inputs[i]);
        for (size_t k = 0; k < m; k++)
        {
            cout << "Class " << k + 1 << " : " << outputsTrained[i][k] * 100 << " %\n";
        }
    }
    std::cout << "Iterations:" << iter << '\n';
    std::cout << "Elapsed: " << duration << " sec.\n";
    std::cout << "=============\n";

    matr ins_noised;

    std::vector<size_t> idxs(n);
    for (size_t i = 0; i < n; i++)
    {
        idxs[i] = i;
    }

    for (size_t i = 0; i < p; i++)
    {
        std::vector<double> input(inputs[i]);
        for (size_t j = 0; j < 3; j++)
        {
            std::shuffle(idxs.begin(), idxs.end(), rng);
            size_t count = n * 20 * (j + 1) / 100;
            for (size_t k = 0; k < count; k++)
            {
                size_t idx = idxs[k];
                input[idx] = fmod(input[idx] + 1.0, 2.0);
            }
            ins_noised.push_back(input);
        }
    }

    for(auto& in_noised: ins_noised)
    {
        DrawImage(in_noised);
        vect out_rec(m);

        vect hid(h);
        for (size_t j = 0; j < h; j++)
        {
            auto centroid = centroids[j];
            double dist = calculateDistance(in_noised, centroid);
            hid[j] = exp(-dist / (2 * widths[j] * widths[j]));
        }

        for (size_t k = 0; k < m; k++)
        {
            double tmp = 0.0;
            for (size_t j = 0; j < h; j++)
            {
                tmp += wHO[j][k] * hid[j];
            }
            out_rec[k] = activate(tmp);
        }

        for (size_t k = 0; k < m; k++)
        {
            cout << "Class " << k + 1 << " : " << out_rec[k] * 100 << " %\n";
        }
    }

    return 0;
}