#include <iostream>
#include <iomanip>

const int N = 15;
int a[N][N];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

//偏移量做法

int main()
{
    int n;
    std::cin >> n;

    int x = 0, y = 0, d = 0, num = 1;

    while(num <= n * n)
    {
        a[x][y] = num++;

        int tempx = x + dx[d], tempy = y + dy[d];
        
        if(tempx < 0 || tempx > n - 1 || tempy < 0 || tempy > n - 1 || a[tempx][tempy])
        //用下一步的状态判断越界
        //a[tempx][tempy] 判断是否填过数
        {
            d = (d + 1) % 4;
        }

        x += dx[d];
        y += dy[d];

    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            std::cout.width(3);
            std::cout << a[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}