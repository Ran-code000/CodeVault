#include <iostream>
#include <vector>

//c++ 中数组（以及类似于数组的std::vector）的索引是从0开始的
//输入的如果是正常的坐标需要 x--, y-- 来调整索引以适应从0开始的计数

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int>(n, 1));

    int m, k;
    std::cin >> m >> k;

    while(m--)
    {
        int x, y;
        std::cin >> x >> y;

        for(int i = std::max(y - 1 - 2, 0); i <= std::min(y - 1 + 2, n - 1); i++)
        {
            vec[x - 1][i] = 0;
        }

        for(int j = std::max(x - 1 - 2, 0); j <= std::min(x - 1 + 2, n - 1); j++)
        {
            vec[j][y - 1] = 0;
        }

        for(int a = std::max(x - 1 - 1, 0); a <= std::min(x - 1 + 1, n - 1); a++)
        {
            for(int t = std::max(y - 1 - 1, 0); t <= std::min(y - 1 + 1, n - 1); t++)
            {
                vec[a][t] = 0;
            }
        }
    }

    while(k--)
    {
        int x, y;
        std::cin >> x >> y;

        for(int i = std::max(x - 1 - 2, 0); i <= std::min(x - 1 + 2, n - 1); i++)
        {
            for(int j = std::max(y - 1 - 2, 0); j <= std::min(y - 1 + 2, n - 1); j++)
            {
                vec[i][j] = 0;
            }
        }
    }

    int ans = 0;
    for(const auto &row : vec)
    {
        for(int val : row)
        {
            if(val) ans++;
        }
    }

    std::cout << ans;

    return 0;
}