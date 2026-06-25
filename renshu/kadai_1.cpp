#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
//ガウスサイデル
int main(void){
    int n;
    std::cout << "Enter size n: ";
    std::cin >> n;

    float f[n+1] = {0.0f}; // f[0]からf[n]までの配列を初期化
    std::cout << "f(0)とf(n)の初期値を入力" << std::endl;
    std::cout << "f(0): ";
    std::cin >> f[0];
    std::cout << "f(" << n << "): ";
    std::cin >> f[n];

    float f_new[n+1] = {}; 

    for (int j = 0; j < 100; ++j){
        for (int i = 1; i < n; ++i){
            f_new[i] = (f[i-1] + f[i+1]) / 2.0;
        }
        for (int i = 1; i < n; ++i){
            f[i] = f_new[i];
        }
            // std::cout << j+1 << "回目結果:" << std::endl;
            // for (int i = 0; i <= n; ++i){
            //     printf("%.4f ",f[i]);
            // }
            // std::cout << std::endl;
    }

    std::cout << "最終結果:" << std::endl;
    for (int i = 0; i <= n; ++i){
        printf("%.4f ",f[i]);
    }
    std::cout << std::endl;
    return 0;
}