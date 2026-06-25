#include<iostream>
#include<iomanip>
#include<cmath>

double function(double a, double b, double c, double d, double x) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

double differential(double a, double b, double c, double d, double x) {
    double h = 1e-5; 
    return (function(a, b, c, d, x + h) - function(a, b, c, d, x - h)) / (2 * h);
}
    
int main() {
    double x;
    double a, b, c, d;
    std::cout << "Enter coefficients a, b, c, d for the cubic function ax^3 + bx^2 + cx + d: " << std::endl;
    std::cin >> a >> b >> c >> d;
    std::cout << "Enter a value for x: " << std::endl;
    std::cin >> x; 
    std::cout << std::fixed << std::setprecision(9) << "The derivative of the function at x = " << x << " is approximately: " << differential(a, b, c, d, x) << std::endl;
    return 0;
}
