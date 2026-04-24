# include <bits/stdc++.h>

void gen_random_matrix(double *A, const int N)
{
    for (size_t i = 0; i < N * N; i++)
    {
        A[i] = 0.0;
    }

    // std::random_device seed_gen;
    // std::mt19937 engine_mt(seed_gen());
    std::mt19937 engine_mt(100);
    std::uniform_real_distribution<> dist_ur1(-1.00, 1.00), dist_ur2(1.01, 1.05);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            A[i * N + j] = dist_ur1(engine_mt);
        }
        A[i * N + i] += (double)N * dist_ur2(engine_mt);
    }
}

void gen_poisson_matrix(double *A, const int N)
{
    for (size_t i = 0; i < N * N; i++)
    {
        A[i] = 0.0;
    }

    for (size_t i = 0; i < N; i++)
    {
        A[i * N + i] = 2.0;
        if (i >= 1)
        {
            A[i * N + i - 1] = -1.0;
        }
        if (i <= N - 2)
        {
            A[i * N + i + 1] = -1.0;
        }
    }
}

void gen_random_vector(double *b, const int N)
{
    for (size_t i = 0; i < N; i++)
    {
        b[i] = 0.0;
    }

    // std::random_device seed_gen;
    // std::mt19937 engine_mt(seed_gen());
    std::mt19937 engine_mt(100);
    std::uniform_real_distribution<> dist_ur(-1.00, 1.00);

    for (size_t i = 0; i < N; i++)
    {
        b[i] = (double)N * dist_ur(engine_mt);
    }
}

double residue_normal_axb(const double *A, const double *x, const double *b, double *Ax, const int N)
{
    double r = 0.0;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            Ax[i] += A[i * N + j] * x[j];
        }
        r += (b[i] - Ax[i]) * (b[i] - Ax[i]);
    }

    double r0 = 0.0;
    for (size_t i = 0; i < N; i++)
    {
        r0 += b[i] * b[i];
    }

    r = sqrt(r / r0);

    return r;
}

void out_axb(const double *Ax, const double *b, const int N)
{
    printf(" Ax = {");
    for (size_t i = 0; i < N - 1; i++)
    {
        printf("%.2f, ", i, Ax[i]);
    }
    printf("%.2f}\n", N - 1, Ax[N - 1]);
    printf("  b = {");
    for (size_t i = 0; i < N - 1; i++)
    {
        printf("%.2f, ", i, b[i]);
    }
    printf("%.2f}\n", N - 1, b[N - 1]);
    printf("\n");
}

void out_bin(const double *a, const int n, const std::string fpath)
{
    std::ofstream fout;
    fout.open(fpath, std::ios::out | std::ios::binary | std::ios::trunc);
    for (size_t i = 0; i < n; i++)
    {
        fout.write((char *)&a[i], sizeof(double));
    }
    fout.close();
}
