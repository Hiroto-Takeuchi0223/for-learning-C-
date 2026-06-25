#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>

int main() {
     int n;
    std::cout << "正方行列のサイズ n を入力: ";
    if (!(std::cin >> n) || n <= 0) return 1;

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> b(n);

    std::cout << "正方行列 A を入力 (行ごと, " << n*n << " 個の値):\n";
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];

    std::cout << "ベクトル b を入力 (" << n << " 個の値):\n";
    for (int i = 0; i < n; ++i) std::cin >> b[i];

    double tol = 1e-8;
    int maxIter = 10000;

    
}