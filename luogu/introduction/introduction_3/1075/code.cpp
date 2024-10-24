#include <iostream>
#include <cmath>

bool isPrime(int n)
{
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <sqrt(n); i += 2)
    {
        if(n % i == 0) return false;
    }

    return true;
}

int main()
{
    int n;
    std::cin >> n;

    for(int i = 2; i < sqrt(n); i++)
    {
        if(n % i == 0 && isPrime(n / i) && isPrime(i))
        {
            std::cout << std::max(i, n / i);
            break;
        }
    }
    return 0;
}