#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

int main() {
    int n;
    std::cout << "Enter size n: ";
    std::cin >> n;

    float f[n+1][n+1] = {};
    std::cout << "境界条件を入力" << std::endl;
    for (int i=0; i<n+1; i++){
        std::cout << "f(0," << i << "): ";
        std::cin >> f[0][i];
    }
    for (int i=0; i<n+1; i++){
        std::cout << "f(" << n << "," << i << "): ";
        std::cin >> f[n][i];
    }
    for (int i=1; i<n; i++){
        std::cout << "f(" << i << ",0): ";
        std::cin >> f[i][0];
    }
    for (int i=1; i<n; i++){
        std::cout << "f(" << i << "," << n << "): ";
        std::cin >> f[i][n];
    }

    float f_new[n+1][n+1] = {};
    for (int i=0; i<100; i++){
        for (int j=1; j<n; j++){
            for (int k=1; k<n; k++){
                f_new[j][k]=(f[j+1][k]+f[j-1][k]+f[j][k+1]+f[j][k-1])/4;
            }
        }
        for (int j=1; j<n; j++){
            for (int k=1; k<n; k++){
                f[j][k] = f_new[j][k];
            }
        }
        }
    

    std::cout << "結果は" << std::endl;
    for (int i=0; i<n+1; i++){
        for (int j=0; j<n+1; j++){
            printf("%6.2f ",f[i][j]);
        }
        std::cout << ""<< std::endl;

    }

    return 0;
}