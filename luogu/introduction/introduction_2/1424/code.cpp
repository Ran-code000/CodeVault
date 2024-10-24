#include <iostream>

int main()
{
    int x, n;
    std::cin >> x >> n;

    int cnt = 0;
    for(int i = 0; i < n; i++)
    //从第 x 天开始算, 包括第 x 天
    {
        int day = (x + i) % 7;
        if(day == 6 || day == 0) cnt++;
    }

    long long ans = (n + 1 - cnt) * 250;
    std::cout << ans;
    return 0;
}