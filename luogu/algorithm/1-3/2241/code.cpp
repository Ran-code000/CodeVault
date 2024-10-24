#include <iostream>

int main()
{
    unsigned long n,m;
    std::cin >> n >> m;

    unsigned long num1 = 0, num2 = 0;

    for(int i = 1; i <= std::min(n,m); i++)
    {
        num1 += (n-i+1)*(m-i+1);
    }

    num2 = ((m + 1)*m/2)*((n + 1)*n/2) - num1;

    std::cout << num1 << " " << num2;

    return 0;
}