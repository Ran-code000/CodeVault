#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int cnt = 1;
    while(n != 1)
    {
        n /= 2;
        cnt++;
    }

    std::cout << cnt;
    return 0;
}