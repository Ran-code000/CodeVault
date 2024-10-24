#include <iostream>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;

    if(n <= 150)
    {
        std::cout << std::fixed << std::setprecision(1) << n * 0.4463;
    }else if(n <= 400)
    {
        std::cout << std::fixed << std::setprecision(1) << 150 * 0.4463 + (n - 150) * 0.4663;
    }else
    {
        std::cout << std::fixed << std::setprecision(1) << 150 * 0.4463 + 250 * 0.4663 + (n - 400) * 0.5663;
    }
    return 0;
}