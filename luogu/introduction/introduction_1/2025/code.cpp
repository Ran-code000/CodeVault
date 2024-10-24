#include <iostream>
#include <cmath>
#include <vector>

//const double N = 5.0;

int main()
{   
    double N;
    //必须要 double， 否则ceil 和 floor 不能用
    std::cin >> N;
    //N 为奇数时才成立

    int max_n = ceil(N / 2); //输出的行数
    int min_n = floor(N / 2); //中间坐标的索引
    std::vector<std::vector<int>> veca(max_n, std::vector<int>(N, 0));
    
    for(int i = 0; i < max_n; i++)
    {
        int left = min_n - i;
        int right = min_n + i;
        for(int j = left; j <= right; j++)
        {
            veca[i][j] = 1;
        }
    }
    for(const auto &row : veca)
    {
        for(int val : row)
        {
            if(val) 
            {
                std::cout << "*";
            }else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    std::vector<std::vector<int>> vecb(max_n - 1, std::vector<int>(N - 1, 0));

    max_n -= 1;
    min_n -= 1;
    for(int i = 0; i < max_n; i++)
    {
        int left = min_n - (min_n - i);
        int right = min_n + (min_n - i);
        for(int j = left; j <= right; j++)
        {
            vecb[i][j] = 1;
        }
    }

    for(const auto &row : vecb)
    {
        for(int val : row)
        {
            if(val) 
            {
                std::cout << "*";
            }else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}