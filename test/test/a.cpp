# include <bits/stdc++.h>
# include "iter.hpp"

using namespace std;
const int N = 64;
const int ITERS = 10 * N * N; /* number of iterations */

int main(int argc, char const *argv[])
{
    double A[N * N] = {0.0};
    // gen_random_matrix(A, N);
    gen_poisson_matrix(A, N);
    // out_bin(A, N * N, "./res/A.bin")

    double b[N] = {0.0};
    gen_random_vector(b, N);
    // out_bin(b, N, "./res/b.bin")

    /* solve [A] (x) = (b) with given (A, b); where [*] is a matrix, and (*) is a vector */
    double x[N] = {0.0};
    for (size_t i = 0; i < N; i++)
    {
        x[i] = 0.1;
    }

    for (size_t k = 0; k < ITERS; k++)
    {
        chrono::system_clock::time_point start, end;

        double y[N] = {0.0};
        for (size_t i = 0; i < N; i++)
        {
            y[i] = x[i];
        }

        start = chrono::system_clock::now();

# pragma omp parallel for num_threads(4) /* Jacobi iteration with OpenMP */
        for (size_t i = 0; i < N; i++)
        {
            x[i] = b[i] + A[i * N + i] * y[i];
            for (size_t j = 0; j < N; j++)
            {
                x[i] -= A[i * N + j] * y[j];
            }
            x[i] /= A[i * N + i];
        }

        end = chrono::system_clock::now();
        double time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);

        /* calculate residue */
        double Ax[N] = {0.0};
        double res = residue_normal_axb(A, x, b, Ax, N);

        /* output */
        printf("%e, %lf\n", res, time); /* residue and time (with openmp) */
        // output_axb(Ax, b);
    }

    cout << endl;

    for (size_t i = 0; i < N; i++)
    {
        x[i] = 0.1;
    }

    for (size_t k = 0; k < ITERS; k++)
    {
        chrono::system_clock::time_point start, end;

        double y[N] = {0.0};
        for (size_t i = 0; i < N; i++)
        {
            y[i] = x[i];
        }

        start = chrono::system_clock::now();

        /* Jacobi iteration without OpenMP */
        for (size_t i = 0; i < N; i++)
        {
            x[i] = b[i] + A[i * N + i] * y[i];
            for (size_t j = 0; j < N; j++)
            {
                x[i] -= A[i * N + j] * y[j];
            }
            x[i] /= A[i * N + i];
        }

        end = chrono::system_clock::now();
        double time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);

        /* calculate residue */
        double Ax[N] = {0.0};
        double res = residue_normal_axb(A, x, b, Ax, N);

        /* output */
        printf("%e, %lf\n", res, time); /* residue and time (without openmp) */
        // output_axb(Ax, b);
    }

    return 0;
}
