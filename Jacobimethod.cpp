#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>

using Vec = std::vector<double>;
using Mat = std::vector<std::vector<double>>;

Vec jacobiSolver(const Mat &A, const Vec &b, const Vec &x0, double tol, int maxIter){
    int n = (int)A.size();
    Vec x = x0;
    Vec xnew(n, 0.0);

    for (int iter = 0; iter < maxIter; ++iter){
        for (int i = 0; i < n; ++i){
            double diag = A[i][i];
            if (std::abs(diag) < std::numeric_limits<double>::epsilon()){
                throw std::runtime_error("Zero diagonal element encountered in Jacobi method");
            }
            double sum = 0.0;
            for (int j = 0; j < n; ++j){
                if (j == i) continue;
                sum += A[i][j] * x[j];
            }
            xnew[i] = (b[i] - sum) / diag;
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) diff = std::max(diff, std::abs(xnew[i] - x[i]));
        x = xnew;
        if (diff <= tol) break;
    }
    return x;
}

int main(){
    int n;
    std::cout << "Enter matrix size n: ";
    if (!(std::cin >> n) || n <= 0) return 1;

    Mat A(n, Vec(n));
    Vec b(n);

    std::cout << "Enter matrix A (row by row, " << n*n << " values):\n";
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];

    std::cout << "Enter vector b (" << n << " values):\n";
    for (int i = 0; i < n; ++i) std::cin >> b[i];

    double tol = 1e-8;
    int maxIter = 10000;

    Vec x0(n, 0.0);
    try{
        Vec x = jacobiSolver(A, b, x0, tol, maxIter);
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "Solution (approx):\n";
        for (int i = 0; i < n; ++i) std::cout << "x[" << i << "] = " << x[i] << "\n";
    } catch (const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}