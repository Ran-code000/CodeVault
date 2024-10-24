#include <iostream>

bool isA(int n);
bool isB(int n);
bool isC(int n);
bool isD(int n);

int main()
{
    int n;
    std::cin >> n;

    if(isA(n))
    {
        std::cout << 1 << " ";
    }else
    {
        std::cout << 0 << " ";
    }

    if(isB(n))
    {
        std::cout << 1 << " ";
    }else
    {
        std::cout << 0 << " ";
    }

    if(isC(n))
    {
        std::cout << 1 << " ";
    }else
    {
        std::cout << 0 << " ";
    }

    if(isD(n))
    {
        std::cout << 1 << " ";
    }else
    {
        std::cout << 0 << " ";
    }
    return 0;
}

bool isA(int n)
{
    if(n % 2 == 0 && n > 4 && n <= 12)
    {
        return true;
    }
    return false;
}
bool isB(int n)
{
    if(n % 2 == 0 || n > 4 && n <= 12)
    {
        return true;
    }
    return false;
}
bool isC(int n)
{
    if(n % 2 == 0 && n <= 4 && n > 12 || n % 2 && n > 4 && n <= 12)
    {
        return true;
    }
    return false;
}
bool isD(int n)
{
    if(!(n % 2 == 0 || n > 4 && n <= 12))
    {
        return true;
    }
    return false;
}