#include <iostream>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;
    int sum = 0;
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }

    int ans = 1;
    n++;
    while(n--)
    {
        for(int i = 0; i < n; i++)
        {
            std::cout << std::setw(2) << std::setfill('0') << ans++;
        }
        std::cout << "\n";
    }
    return 0;
}