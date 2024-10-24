#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    n--;
    int ans = 1;
    while(n--)
    {
        ans = (ans + 1) * 2;
    }

    std::cout << ans;

    return 0;
}