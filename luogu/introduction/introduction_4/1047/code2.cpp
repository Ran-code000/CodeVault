#include <iostream>

//用差分数组的方法

const int N = 1e5 + 10;
int a[N], s[N];

int main()
{
    int n, m;
    std::cin >> n >> m;

    while(m--)
    {
        int l, r;
        std::cin >> l >> r;
        l++, r++;
        a[l]++, a[r + 1]--;
    }

    int ans = n + 1;
    for(int i = 1; i < N; i++)
    {
        s[i] = s[i - 1] + a[i];
        if(s[i]) ans--;
    }

    std::cout << ans;

}