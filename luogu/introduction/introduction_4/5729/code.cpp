#include <iostream>
#include <vector>

//暴力即可

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<std::vector<int>>> v(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(k + 1, 0)));
    //int v[35][35][35];

    int t;
    std::cin >> t;
    while(t--)
    {
        int x1, y1, z1, x2, y2, z2;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        for(int x = x1; x <= x2; x++)
        {
            for(int y = y1; y <= y2; y++)
            {
                for(int z = z1; z <= z2; z++)
                {
                    v[x][y][z] = 1;
                }
            }
        }
    }

    int ans = n * m * k;
    for(int x = 1; x <= n; x++)
    {
        for(int y = 1; y <= m; y++)
        {
            for(int z = 1; z <= k; z++)
            {
                if(v[x][y][z]) ans--;
            }
        }
    }

    std::cout << ans;

    return 0;

}