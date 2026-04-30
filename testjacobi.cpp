#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>

int main() {
     int n;
    std::cout << "Enter matrix size n: ";
    if (!(std::cin >> n) || n <= 0) return 1;

    Mat A(n, Vec(n));
    Vec b(n);

    std::cout << "Enter matrix A (row by row, " << n*n << " values):\n";
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];

    std::cout << "Enter vector b (" << n << " values):\n";
    for (int i = 0; i < n; ++i) std::cin >> b[i];

    if
}