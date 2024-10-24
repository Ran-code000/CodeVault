#include <iostream>

int main()
{
    int max = -1;
    int sadDay = 0;
    int flag = 1;
    for(int i = 1; i <= 7; i++)
    {
        int sum = 0;
        int a, b;
        std::cin >> a >> b;
        sum = a + b;
        if(sum >= 8)
        {
            flag = 0;
            if(sum > max)
            {
                max = sum;
                sadDay = i;
            }
        }
    }

    if(flag)
    {
        std::cout << 0;
        return 0;
    }

    std::cout << sadDay;

    return 0;
}