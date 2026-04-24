#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>


double LSE(){
    int n;
    std::cout << "Enter the size of the square matrix: " << std::endl;
    std::cin >> n;
    std::vector<std::vector<double>> A(n,std::vector<double>(n)) ;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "Enter element (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> A[i][j];
        }
    }
    
    
    std::vector<std::vector<double>> B(n,std::vector<double>(n)) ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "Enter element (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> B[i][j];
        }
    }
    return A, B;
}
    
int main(void){
    for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            std::cout << A[i][j] << std::endl;
        }
    }

}