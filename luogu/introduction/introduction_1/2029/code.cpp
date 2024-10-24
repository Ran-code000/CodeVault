#include <iostream>
#include <cmath>

int main()
{
    int h,r;
    std::cin >> h >> r;
    
    std::cout << ceil(20000/(3.14*r*r*h)) << std::endl;

    return 0;
}