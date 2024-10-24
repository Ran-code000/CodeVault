#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int> (n, 0));

    int size = (int)std::pow(n, 2);

    int i = 0, j = n / 2;
    int num = 1;

    //归纳题意，简化逻辑
    while(size--)
    {
        vec[i][j] = num++;

        int nexti = (i - 1 + n) % n;
        int nextj = (j + 1 + n) % n;
        //注意需要 %n
        //解决数组越界问题，类比 c 中的大小写加密

        if(vec[nexti][nextj])
        {
            i = (i + 1 + n) % n;
        }else
        {
            i = nexti;
            j = nextj;
        }
    }

    for(const auto &row : vec)
    {
        for(int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    
    
    return 0;
}