#include <iostream>

int main()
{
    int k;
    std::cin >> k;

    double sum = 0;
    for(int i = 1; ; i++)
    {
        sum += (double)1 / i;
        if(sum > k)
        {
            std::cout << i;
            break;
        }
    }
    return 0;
}