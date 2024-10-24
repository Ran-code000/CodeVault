#include <iostream>
#include <cmath>

bool isPrime(int num);

int main()
{
    int n;
    std::cin >> n;

    if(isPrime(n))
    {
        std::cout << n;
    }

    if(n % 2 == 0 && isPrime(n / 2))
    {
        int t = n / 2;
        if(isPrime(t))
        {
            std::cout << std::max(t,2) << std::endl;
        }
    }//将其中一个是质数 2 的情况提出来单独讨论，快了 1ms

    for(int i = 3; i < sqrt(n); i+=2)
    {
        if(n % i == 0 && isPrime(i))
        {
            int t = n / i;
            if(isPrime(t))
            {
                std::cout << std::max(t,i) << std::endl;
            }
        }
    }
    
    return 0;
}

bool isPrime(int num)
{
    if(num == 1) return false;
    if(num == 2) return true;
    if(num % 2 == 0) return false;
    for(int i = 3; i <= sqrt(num); i+=2)
    {
        if(num % i == 0)
        {
            return false;
        }
    }

    return true;
}

