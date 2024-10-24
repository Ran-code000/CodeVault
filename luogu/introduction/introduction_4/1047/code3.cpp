#include <iostream>
#include <vector>

int main()
{
    int l, m;
    std::cin >> l >> m;

    std::vector<int> vec(l + 1, 0);

    while(m--)
    {
        int left, right;
        std::cin >> left >> right;

        for(int i = left; i <= right; i++)
        {
            vec[i] = 1;
        }
    }

    int ans = 0;
    for(const auto &val : vec)
    {
        if(val == 0)
        {
            ans++;
        }
    }
    std::cout << ans;

    return 0;
}