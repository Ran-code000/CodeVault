#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int sum1 = 0, sum2 = 0;
    for(int i = 1;; i++)
    {
        sum1 += i;
        sum2 += i*i;

        if(sum1 > n)
        {
            sum1 -= i;
            sum2 -= i*i;
            sum2 += (n - sum1) * i;
            break;
        }
    }

    std::cout << sum2;
    return 0;
}