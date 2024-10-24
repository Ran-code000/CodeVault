#include <iostream>
#include <climits>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;

    int min = INT_MAX;
    for(int i  = 0; i < 3; i++)
    {
        int num, price;
        std::cin >> num >> price;

        int spend = ceil((double)n / num) * price;
        if(spend < min) min = spend;
    }

    std::cout << min;
    return 0;
}