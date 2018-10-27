#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>

#include "MLP.h"

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

vect createRandomVector(size_t size)
{
    vect res(size);
    for (size_t i = 0; i < size; i++)
    {
        res[i] = -1 + (rand() / (RAND_MAX / 2.0));
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

matr createRandomMatrix(const size_t &n, const size_t &h);

int main()
{
    size_t n = 36, h = 6, m = 5, p = 5;

    MLP mlp({ n,h,m });

    std::vector<TrainingSample> sample;
    sample.reserve(p);
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
        // ⊃
        {
            1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
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

    for (size_t i = 0; i < p; i++)
    {
        sample.push_back(TrainingSample(inputs[i], outputs[i]));
    }

    mlp.train(sample, TrainConfig());

    //vect hid(h);
    //matr outputsTrained(m, vect(m));
    

    //vect Q = createRandomVector(h);
    //vect T = createRandomVector(m);

    //double alpha, beta;
    //alpha = beta = 1.0;
    //matr wIH = createRandomMatrix(n, h);
    ///*for (size_t i = 0; i < n; i++)
    //{
    //    for (size_t j = 0; j < h; j++)
    //    {
    //        cout << wIH[i][j] << ", ";
    //    }
    //    cout << '\n';
    //}
    //cout << '\n';*/
    //matr wHO = createRandomMatrix(h, m);
    ///*for (size_t i = 0; i < h; i++)
    //{
    //    for (size_t j = 0; j < m; j++)
    //    {
    //        cout << wHO[i][j] << ", ";
    //    }
    //    cout << '\n';
    //}*/
    //matr ferr(p, vect(m));

    //std::clock_t start;
    //double duration;

    //start = std::clock();

    //size_t iter = 0;
    //do
    //{
    //    for (size_t idx = 0; idx < p; idx++)
    //    {
    //        vect in = inputs[idx];
    //        vect out = outputsTrained[idx];
    //        vect outReal = outputs[idx];
    //        //DrawImage(in);
    //        //cout << "======\n";
    //        for (size_t j = 0; j < h; j++)
    //        {
    //            double tmp = 0.0;
    //            for (size_t i = 0; i < n; i++)
    //            {
    //                tmp += wIH[i][j] * in[i];
    //            }
    //            hid[j] = activate(tmp + Q[j]);
    //        }

    //        for (size_t k = 0; k < m; k++)
    //        {
    //            double tmp = 0.0;
    //            for (size_t j = 0; j < h; j++)
    //            {
    //                tmp += wHO[j][k] * hid[j];
    //            }
    //            out[k] = activate(tmp + T[k]);
    //        }

    //        vect err(m);
    //        vect out_delta(m);

    //        for (size_t k = 0; k < m; k++)
    //        {
    //            err[k] = outReal[k] - out[k];
    //            ferr[idx][k] = err[k];
    //            out_delta[k] = err[k] * sigmoidDerivative(out[k]);
    //        }

    //        vect hid_err(h);
    //        vect hid_delta(h);

    //        for (size_t j = 0; j < h; j++)
    //        {
    //            for (size_t k = 0; k < m; k++)
    //            {
    //                hid_err[j] += out_delta[k] * wHO[j][k];
    //            }
    //            hid_delta[j] = hid_err[j] * sigmoidDerivative(hid[j]);
    //        }

    //        for (size_t k = 0; k < m; k++)
    //        {
    //            for (size_t j = 0; j < h; j++)
    //            {
    //                wHO[j][k] += alpha * out_delta[k] * hid[j];
    //            }
    //            T[k] += alpha * out_delta[k];
    //        }

    //        for (size_t j = 0; j < h; j++)
    //        {
    //            for (size_t i = 0; i < n; i++)
    //            {
    //                wIH[i][j] += beta * hid_delta[j] * in[i];
    //            }
    //            Q[j] += beta * hid_delta[j];
    //        }
    //        outputsTrained[idx] = out;
    //    }
    //    iter++;
    //} while (maxAbs(ferr) >= 0.01);

    //duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    //std::cout << "=============\n";
    //std::cout << "Train stats:\n";
    //for (size_t i = 0; i < p; i++)
    //{
    //    DrawImage(inputs[i]);
    //    for (size_t k = 0; k < m; k++)
    //    {
    //        cout << "Class " << k + 1 << " : " << outputsTrained[i][k] * 100 << " %\n";
    //    }
    //}
    //std::cout << "Iterations:" << iter << '\n';
    //std::cout << "Elapsed: " << duration << " sec.\n";
    //std::cout << "=============\n";

    //matr ins_noised(inputs);
    //ins_noised.push_back(
    //    {
    //        0.0,0.0,0.0,0.0,1.0,1.0,
    //        1.0,1.0,1.0,1.0,1.0,1.0,
    //        1.0,1.0,1.0,1.0,1.0,1.0,
    //        1.0,1.0,1.0,1.0,1.0,1.0,
    //        1.0,1.0,0.0,0.0,0.0,0.0,
    //        1.0,1.0,1.0,1.0,1.0,1.0
    //    });
    //
    //for (auto in_noised : ins_noised)
    //{
    //    DrawImage(in_noised);
    //    vect out_rec(m);

    //    for (size_t i = 0; i < h; i++)
    //    {
    //        double tmp = 0.0;
    //        for (size_t j = 0; j < n; j++)
    //        {
    //            tmp += wIH[j][i] * in_noised[j];
    //        }
    //        hid[i] = activate(tmp + Q[i]);
    //    }

    //    for (size_t k = 0; k < m; k++)
    //    {
    //        double tmp = 0.0;
    //        for (size_t j = 0; j < h; j++)
    //        {
    //            tmp += wHO[j][k] * hid[j];
    //        }
    //        out_rec[k] = activate(tmp + T[k]);
    //    }

    //    for (size_t k = 0; k < m; k++)
    //    {
    //        cout << "Class " << k + 1 << " : " << out_rec[k] * 100 << " %\n";
    //    }
    //}

    return 0;
}

matr createRandomMatrix(const size_t &n, const size_t &k)
{
    matr m(n, vect(k));
    for (size_t i = 0; i < n; i++)
    {
        m[i] = createRandomVector(k);
    }
    return m;
}