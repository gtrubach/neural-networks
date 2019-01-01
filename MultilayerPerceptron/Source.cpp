#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

using vect = vector<double>;
using matr = vector<vector<double>>;

double activate(double value)
{
    return 1.0 / (1.0 + exp(-value));
}

double sigmoidDerivative(double value)
{
    return value * (1.0 - value);
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

double getError(double ideal, double expected)
{
    return ideal - expected;
}

double max(vect arr)
{
    double tmp = arr[0];

    for (auto el : arr)
    {
        if (el > tmp) tmp = el;
    }

    return tmp;
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
    uniform_real_distribution<double>& distr);

vect calcLayer(const size_t &n,
    const size_t &h,
    const vect &in,
    const vect &thresholds,
    const matr &weights);

void updateWeightsAndThresholds(const size_t &m,
    const size_t &h,
    const double &speed,
    const vect &delta,
    const vect &layer,
    matr &weights,
    vect &thresholds);

int main()
{
    size_t n = 36, h = 18, m = 5, p = 5;

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

    vect hid(h);
    matr outputsTrained(m, vect(m));

    auto seed = (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution<double> distr(-1.0, 1.0);

    vect Q = createRandomVector(h, rng, distr);
    vect T = createRandomVector(m, rng, distr);

    double alpha, beta;
    alpha = 2;
    beta = 3;
    matr wIH = createRandomMatrix(n, h, rng, distr);
    matr wHO = createRandomMatrix(h, m, rng, distr);
    matr ferr(p, vect(m));

    std::clock_t start;
    double duration;

    start = std::clock();

    size_t iter = 0;
    do
    {
        for (size_t idx = 0; idx < p; idx++)
        {
            vect in = inputs[idx];
            vect out = outputsTrained[idx];
            vect outReal = outputs[idx];

            hid = calcLayer(n, h, in, Q, wIH);
            out = calcLayer(h, m, hid, T, wHO);

            vect err(m);
            vect out_delta(m);

            for (size_t k = 0; k < m; k++)
            {
                err[k] = outReal[k] - out[k];
                ferr[idx][k] = err[k];
                out_delta[k] = err[k] * sigmoidDerivative(out[k]);
            }

            vect hid_err(h);
            vect hid_delta(h);

            for (size_t j = 0; j < h; j++)
            {
                for (size_t k = 0; k < m; k++)
                {
                    hid_err[j] += out_delta[k] * wHO[j][k];
                }
                hid_delta[j] = hid_err[j] * sigmoidDerivative(hid[j]);
            }

            updateWeightsAndThresholds(m, h, alpha, out_delta, hid, wHO, T);
            updateWeightsAndThresholds(h, n, beta, hid_delta, in, wIH, Q);

            outputsTrained[idx] = out;
        }
        iter++;
    } while (maxAbs(ferr) >= 0.01);

    duration = ((double)std::clock() - start) / (double)CLOCKS_PER_SEC;
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

    for (auto in_noised : ins_noised)
    {
        DrawImage(in_noised);
        vect out_rec(m);

        for (size_t i = 0; i < h; i++)
        {
            double tmp = 0.0;
            for (size_t j = 0; j < n; j++)
            {
                tmp += wIH[j][i] * in_noised[j];
            }
            hid[i] = activate(tmp + Q[i]);
        }

        for (size_t k = 0; k < m; k++)
        {
            double tmp = 0.0;
            for (size_t j = 0; j < h; j++)
            {
                tmp += wHO[j][k] * hid[j];
            }
            out_rec[k] = activate(tmp + T[k]);
        }

        for (size_t k = 0; k < m; k++)
        {
            cout << "Class " << k + 1 << " : " << out_rec[k] * 100 << " %\n";
        }
    }

    return 0;
}

void updateWeightsAndThresholds(const size_t &m,
    const size_t &h,
    const double &speed,
    const vect &delta,
    const vect &layer,
    matr &weights,
    vect &thresholds)
{
    for (size_t k = 0; k < m; k++)
    {
        for (size_t j = 0; j < h; j++)
        {
            weights[j][k] += speed * delta[k] * layer[j];
        }
        thresholds[k] += speed * delta[k];
    }
}

vect calcLayer(const size_t &n,
    const size_t &h,
    const vect &in,
    const vect &thresholds,
    const matr &weights)
{
    vect layer(h);
    for (size_t j = 0; j < h; j++)
    {
        double tmp = 0.0;
        for (size_t i = 0; i < n; i++)
        {
            tmp += weights[i][j] * in[i];
        }
        layer[j] = activate(tmp + thresholds[j]);
    }
    return layer;
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