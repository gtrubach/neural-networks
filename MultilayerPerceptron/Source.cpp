#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

using vect = vector<double>;
using matr = vector<vector<double>>;

double activate(double value)
{
    return 1.0 / (1.0 + exp(-value));
}

double sigmoidDerivative(double value)
{
    return value * (1 - value);
}

vect generateRandom(size_t size)
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

int main()
{
    size_t n = 36, h = 6, m = 5;
    vect in =
    {
        1.0,1.0,1.0,1.0,1.0,1.0,
        0.0,0.0,0.0,0.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0,
        0.0,0.0,0.0,0.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0
    };
    DrawImage(in);
    vect hid(h);
    vect out(m);
    vect outReal = { 0.0,0.0,1.0,0.0,0.0 };

    vect Q(generateRandom(h));
    vect T(generateRandom(m));

    double alpha, beta;
    alpha = beta = 1;

    matr wIH(n, vect(h));
    for (size_t i = 0; i < n; i++)
    {
        wIH[i] = generateRandom(h);
    }
    matr wHO(h, vect(m));
    for (size_t i = 0; i < h; i++)
    {
        wHO[i] = generateRandom(m);
    }

    vect ferr(m);

    do
    {
        for (size_t i = 0; i < h; i++)
        {
            double tmp = 0.0;
            for (size_t j = 0; j < n; j++)
            {
                tmp += wIH[j][i] * in[j];
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
            out[k] = activate(tmp + T[k]);
        }

        vect err(m);
        vect out_delta(m);

        for (size_t k = 0; k < m; k++)
        {
            err[k] = outReal[k] - out[k];
            ferr[k] = fabs(err[k]);
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

        for (size_t k = 0; k < m; k++)
        {
            for (size_t j = 0; j < h; j++)
            {
                wHO[j][k] += alpha * out_delta[k] * hid[j];
            }
            T[k] += alpha * out_delta[k];
        }

        for (size_t j = 0; j < h; j++)
        {
            for (size_t i = 0; i < n; i++)
            {
                wIH[i][j] += beta * hid_delta[j] * in[i];
            }
            Q[j] += beta * hid_delta[j];
        }
    } while (max(ferr) > 0.01);

    vect in_noised =
    {
        0.0,0.0,0.0,0.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0,
        1.0,1.0,1.0,1.0,1.0,1.0,
        1.0,1.0,0.0,0.0,0.0,0.0,
        1.0,1.0,1.0,1.0,1.0,1.0
    };

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

    return 0;
}