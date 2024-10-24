#include <iostream>

bool isLeapyear(int n)
{
    if(n % 4 == 0 && n % 100 || n % 400 == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    int year, month;
    std::cin >> year >> month;

    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 )
    {
        std::cout << 31;
    }else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
        std::cout << 10;
    }else if(month == 2)
    {
        if(isLeapyear(year))
        {
            std::cout << 29;
        }else
        {
            std::cout << 28;
        }
    }
    return 0;
}