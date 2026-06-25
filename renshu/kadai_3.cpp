#include <iostream> 
#include <cmath>

double dot_product(double a[], double b[], int n) {
    double sum = 0.0;
    for (int i=0; i<n; i++){
        sum += a[i] * b[i];
    }
    return sum;
}

double matrix_vector_product(int n, double A[][n], double x[], double result[], int k) {
    for (int i=0; i<n; i++){
        result[i] = 0.0;
        for (int j=0; j<n; j++){
            result[i] += A[i][j] * x[j];
        }
    }
    return result[k]; 
}

int main() {
    int n;
    std::cout << "Enter size n: ";
    std::cin >> n;

    double f[n][n] = {};
    std::cout << "境界条件を入力" << std::endl;
    for (int i=0; i<n; i++){
        std::cout << "f(0," << i << "): ";
        std::cin >> f[0][i];
    }
    for (int i=0; i<n; i++){
        std::cout << "f(" << n-1 << "," << i << "): ";
        std::cin >> f[n-1][i];
    }
    for (int i=1; i<n-1; i++){
        std::cout << "f(" << i << ",0): ";
        std::cin >> f[i][0];
    }
    for (int i=1; i<n-1; i++){
        std::cout << "f(" << i << "," << n-1 << "): ";
        std::cin >> f[i][n-1];
    }

    double A[n][n] = {};
    double h = 1e-8;

    for (int i=0; i<n; i++){
        A[i][i] = -4/h;
    }
    for (int i=0; i<n-1; i++){
        A[i][i+1] = 1/h;
        A[i+1][i] = 1/h;
    }

    double b[n] = {};
    for (int i=1; i<n; i++){
        std::cout << "b(" << i << "): ";
        std::cin >> b[i];
    }

    double x[n] ={}; // initial solution
    double r[n] = {}; // initial difference
    for (int i=0; i<n; i++){
        r[i] = b[i] - matrix_vector_product(n, A, x, r, i);
    }
    double c1 = dot_product(r, r, n);
    if (c1 < 1e-8){return 0;}

    double p[n] = {}; // initial search direction
    double r0[n] = {};
    for (int i=0; i<n; i++){
        p[i] = r[i];
        r0[i] = r[i];
    }
    for (int k=0; k<n; k++){
        double y[n] = {};
        for (int i=0; i<n; i++){
            y[i] = matrix_vector_product(n, A, p, y, i);
        }
        double c2 = dot_product(r0, y, n);
        double alpha = c1 / c2;
        double e[n] = {};
        for (int i=0; i<n; i++){
            e[i] = r[i] - alpha * y[i];
        }
        double v[n] = {};
        for (int i=0; i<n; i++){
            v[i] = matrix_vector_product(n, A, e, v, i);
        }
        double ev = dot_product(e, v, n);
        double vv = dot_product(v, v, n);
        double c3 = ev / vv;
        for (int i=0; i<n; i++){
            x[i] = x[i] + alpha * p[i] + c3 * e[i];
            r[i] = e[i]- c3 * v[i];
        }
        double rr = dot_product(r, r, n);
        std::cout << "Iteration " << k+1 << ": Residual = " << rr << std::endl;
        if (rr < 1e-8){
            std::cout << "Convergence achieved after " << k+1 << " iterations." << std::endl;
            break;
        }
        c1 = dot_product(r0, r, n);
        double beta = c1 / c2 / c3;
        for (int i=0; i<n; i++){
            p[i] = r[i] + beta * (p[i] - c3 * v[i]);
        }

        for (int i=0; i<n; i++){
            std::cout << "x(" << i << "): " << x[i] << std::endl;
        }
        return 0;
    }

    return 0;
}   