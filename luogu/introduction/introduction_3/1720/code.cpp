#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;

    double c1 = (1.0 + std::sqrt(5)) / 2.0;
    double c2 = (1.0 - std::sqrt(5)) / 2.0;
    double ans = (pow(c1, n) - pow(c2, n)) / std::sqrt(5);

    std::cout << std::fixed << std::setprecision(2) << ans;

    return 0;
}