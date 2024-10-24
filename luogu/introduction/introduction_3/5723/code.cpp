#include <iostream>
#include <cmath>

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
int main()
{
    int n;
    std::cin >> n;

    int sum = 0;
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        

        if(isPrime(i))
        {
            sum += i;
            if(sum > n) break;
            cnt++;
            std::cout << i << "\n";
        }

    }

    std::cout << cnt;
    return 0;
}