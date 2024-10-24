#include <iostream>

int main()
{
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i <= 12; i++)
    {
        int x;
        std::cin >> x;

        sum1 += (300 - x);

        if(sum1 < 0)
        {
            std::cout << "-" << i;
            return 0;
        }else if(sum1 >= 100)
        {
            sum2 += sum1 / 100;
            sum1 %= 100;
        }else
        {
            continue;
        }
    }

    std::cout << sum1 + sum2 * 100 * 1.2;

    return 0;
}