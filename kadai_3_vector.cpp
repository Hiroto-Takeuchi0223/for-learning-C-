// BiCGSTAB implementation in C++
// Simple, single-file program that demonstrates BiCGSTAB with
// intermediate progress output so you can study the algorithm.

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using Vec = std::vector<double>;

double norm(const Vec &v) {
    double s = 0.0;
    for (double x : v) s += x*x;
    return std::sqrt(s);
}

// y = A*x for dense matrix A stored as vector of vectors
void matvec(const std::vector<Vec> &A, const Vec &x, Vec &y) {
    int n = (int)A.size();
    y.assign(n, 0.0);
    for (int i = 0; i < n; ++i) {
        double s = 0.0;
        for (int j = 0; j < n; ++j) s += A[i][j] * x[j];
        y[i] = s;
    }
}

// BiCGSTAB solver
// A: matrix (dense), b: rhs, x: initial guess and output, tol: tolerance, maxit: max iterations
bool bicgstab(const std::vector<Vec> &A, const Vec &b, Vec &x,
              double tol = 1e-8, int maxit = 1000, bool verbose = true) {
    int n = (int)b.size();
    Vec r(n), rtilde(n), p(n), v(n), s(n), t(n), tmp(n);

    matvec(A, x, tmp);
    for (int i = 0; i < n; ++i) r[i] = b[i] - tmp[i];
    rtilde = r; // choose r0_hat = r0

    double rho_old = 1.0, alpha = 1.0, omega = 1.0;
    p.assign(n, 0.0); v.assign(n, 0.0);

    double bnorm = norm(b);
    if (bnorm == 0.0) bnorm = 1.0;
    double rnorm = norm(r);
    if (verbose) std::cout << "iter 0, res = " << rnorm / bnorm << "\n";
    if (rnorm / bnorm < tol) return true;

    for (int iter = 1; iter <= maxit; ++iter) {
        double rho = 0.0;
        for (int i = 0; i < n; ++i) rho += rtilde[i] * r[i];
        if (std::abs(rho) < 1e-30) return false;

        double beta = (rho / rho_old) * (alpha / omega);
        for (int i = 0; i < n; ++i) p[i] = r[i] + beta * (p[i] - omega * v[i]);

        matvec(A, p, v);
        double rtv = 0.0;
        for (int i = 0; i < n; ++i) rtv += rtilde[i] * v[i];
        if (std::abs(rtv) < 1e-30) return false;
        alpha = rho / rtv;

        for (int i = 0; i < n; ++i) s[i] = r[i] - alpha * v[i];

        double snorm = norm(s);
        if (snorm / bnorm < tol) {
            for (int i = 0; i < n; ++i) x[i] += alpha * p[i];
            if (verbose) std::cout << "iter " << iter << ", res = " << snorm / bnorm << " (converged after phi)\n";
            return true;
        }

        matvec(A, s, t);
        double tt = 0.0, ts = 0.0;
        for (int i = 0; i < n; ++i) { tt += t[i] * t[i]; ts += t[i] * s[i]; }
        if (std::abs(tt) < 1e-30) return false;
        omega = ts / tt;

        for (int i = 0; i < n; ++i) x[i] += alpha * p[i] + omega * s[i];

        for (int i = 0; i < n; ++i) r[i] = s[i] - omega * t[i];

        rnorm = norm(r);
        if (verbose) std::cout << "iter " << iter << ", res = " << rnorm / bnorm << "\n";
        if (rnorm / bnorm < tol) return true;

        if (std::abs(omega) < 1e-30) return false;
        rho_old = rho;
    }
    return false;
}

// Simple test: diagonally dominant matrix so BiCGSTAB should converge
int main() {
    int n = 10;
    std::vector<Vec> A(n, Vec(n, 0.0));
    Vec b(n, 1.0);
    Vec x(n, 0.0);

    // build a symmetric positive definite-like matrix (diagonally dominant)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) A[i][j] = 4.0;
            else if (std::abs(i-j) == 1) A[i][j] = -1.0;
            else A[i][j] = 0.0;
        }
    }

    std::cout << "Solving Ax=b with BiCGSTAB (n=" << n << ")\n";
    bool ok = bicgstab(A, b, x, 1e-8, 1000, true);
    if (ok) std::cout << "Converged" << std::endl;
    else std::cout << "Not converged" << std::endl;

    std::cout << "Solution x (first 10 entries):\n";
    for (int i = 0; i < std::min(n, 10); ++i) std::cout << x[i] << "\n";
    return 0;
}
