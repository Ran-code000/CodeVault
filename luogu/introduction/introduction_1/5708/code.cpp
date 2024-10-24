#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;

    const double p = (a + b + c) / 2;
    double sum = std::sqrt(p * (p - a) * (p - b) * (p - c));

    std::cout << std::fixed << std::setprecision(1) << sum;

    return 0;
}