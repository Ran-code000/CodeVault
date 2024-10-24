#include <iostream>
#include <cmath>

bool isPrime(int n);

int main()
{
    int n;
    std::cin >> n;

    for(int i = 4; i <= n; i+=2)
    {
        for(int j = 2; j <= (i / 2) + 1; j++)
        {
            if(isPrime(j) && isPrime(i - j))
            {
                std::cout << i << "=" << j << "+" << i - j << std::endl;
                break;
            }
        }
    }
    return 0;
}

bool isPrime(int n)
{
    if(n == 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;

    for(int i = 3; i <= sqrt(n); i++)
    {
        if(n % i == 0)
        {
            return false;
        }
    }

    return true;
}
