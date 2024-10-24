#include <iostream>

int f(int num)
{
    if(num == 0)
    {
        return 0;
    }
    if(num == 1)
    {
        return num;
    }

    return num * f(num-1);
}

int main()
{
    int num;
    std::cin >> num;

    int ans = f(num);

    std::cout << ans;

    return 0;
}