#include <iostream>

bool isLeapyear(int n)
{
    if(n % 4 == 0 && n % 100 != 0 || n % 400 == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    int n;
    std::cin >> n;

    if(isLeapyear(n))
    {
        std::cout << 1;
    }else
    {
        std::cout << 0;
    }

    return 0;
}