#include <iostream>
#include <cmath>

double dot(double** a, double** b, int N){
    double s = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            s += a[i][j] * b[i][j];
    return s;
}

// ラプラシアン A*x
void A_mul(double** x, double** Ax, int N){
    for (int i = 1; i < N-1; i++){
        for (int j = 1; j < N-1; j++){
            Ax[i][j] =
                4.0 * x[i][j]
                - x[i+1][j]
                - x[i-1][j]
                - x[i][j+1]
                - x[i][j-1];
        }
    }
}

int main(){

    int N;
    std::cout << "Enter size N: ";
    std::cin >> N;

    // 動的2次元配列
    double** x = new double*[N];
    double** b = new double*[N];
    double** r = new double*[N];
    double** p = new double*[N];
    double** Ap = new double*[N];
    double** Ax = new double*[N];

    for (int i = 0; i < N; i++){
        x[i] = new double[N]{0};
        b[i] = new double[N]{0};
        r[i] = new double[N]{0};
        p[i] = new double[N]{0};
        Ap[i] = new double[N]{0};
        Ax[i] = new double[N]{0};
    }

    // ------------------------
    // 境界条件入力
    // ------------------------
    std::cout << "top row:\n";
    for (int j = 0; j < N; j++) std::cin >> x[0][j];

    std::cout << "bottom row:\n";
    for (int j = 0; j < N; j++) std::cin >> x[N-1][j];

    std::cout << "left column:\n";
    for (int i = 0; i < N; i++) std::cin >> x[i][0];

    std::cout << "right column:\n";
    for (int i = 0; i < N; i++) std::cin >> x[i][N-1];

    // bは0（ラプラス）
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            b[i][j] = 0.0;

    // 初期残差
    A_mul(x, Ax, N);

    for (int i = 1; i < N-1; i++){
        for (int j = 1; j < N-1; j++){
            r[i][j] = b[i][j] - Ax[i][j];
            p[i][j] = r[i][j];
        }
    }

    double tol = 1e-6;

    for (int iter = 0; iter < 10000; iter++){

        A_mul(p, Ap, N);

        double rr = 0.0;
        double pAp = 0.0;

        for (int i = 1; i < N-1; i++){
            for (int j = 1; j < N-1; j++){
                rr += r[i][j] * r[i][j];
                pAp += p[i][j] * Ap[i][j];
            }
        }

        // ❗重要：0除算防止
        if (fabs(pAp) < 1e-14){
            std::cout << "break: pAp ~ 0\n";
            break;
        }

        double alpha = rr / pAp;

        // 更新
        for (int i = 1; i < N-1; i++){
            for (int j = 1; j < N-1; j++){
                x[i][j] += alpha * p[i][j];
            }
        }

        double rr_new = 0.0;

        for (int i = 1; i < N-1; i++){
            for (int j = 1; j < N-1; j++){
                r[i][j] = r[i][j] - alpha * Ap[i][j];
                rr_new += r[i][j] * r[i][j];
            }
        }

        if (std::sqrt(rr_new) < tol){
            std::cout << "converged at iter " << iter << "\n";
            break;
        }

        double beta = rr_new / rr;

        for (int i = 1; i < N-1; i++){
            for (int j = 1; j < N-1; j++){
                p[i][j] = r[i][j] + beta * p[i][j];
            }
        }
    }

    // 出力
    std::cout << "solution:\n";
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            std::cout << x[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}