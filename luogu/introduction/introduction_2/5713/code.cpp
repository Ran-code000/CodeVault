#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    
    if(5 * n < 3 * n + 11)
    {
        std::cout << "Local";
    }else
    {
        std::cout << "Luogu";
    }

    return 0;
}