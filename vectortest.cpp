#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>

int main(void){
    std::vector<std::vector<double>> vv(3,std::vector<double>(3)) ;

    vv = {{1, 2, 3},
          {4, 5, 6},
          {7, 8, 9}};  

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << vv[i][j] << std::endl;
        }
    }
    return 0;
}