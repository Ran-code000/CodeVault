#include <iostream>

int main()
{
    int t;
    std::cin >> t;

    for(int x = 100; x >= 1; x--)
    {
        for(int k = 1; ; k++)
        {
            int sum = (x + 3 * k) * 7 * 52;
            if(sum == t) 
            {
                std::cout << x << "\n" << k;
                return 0;
            }else if(sum > t)
            {
                break;
            }else
            {
                continue;
            }
        }
    }
    return 0;
}