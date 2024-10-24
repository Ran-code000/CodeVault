#include <iostream>
#include <cmath>

bool isPrime(int n);
bool isPalindrome(int n);

int main()
{
    int n, m;
    std::cin >> n >> m;

    for(int i = n; i <= m; i++)
    {
        if(isPalindrome(i) && isPrime(i))
        {
            std::cout << i << "\n";
        }
    }

    return 0;
}

bool isPrime(int n)
{
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= std::sqrt(n); i += 2)
    {
        if(n % i == 0) return false;
    }
    return true;
}

bool isPalindrome(int n)
{
    int original = n;
    int reversed = 0;
    
    while(n)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    if(reversed == original) return true;
    return false;
}