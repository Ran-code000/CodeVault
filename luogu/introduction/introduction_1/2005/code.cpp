#include <iostream>
#include <cmath>
#include <vector>

const double N = 5.0;

int main()
{
    char x;
    std::cin >> x;

    int max_n = ceil(N / 2);
    int min_n = floor(N / 2);
    std::vector<std::vector<int>> vec(max_n, std::vector<int>(N, 0));

    for(int i = 0; i < max_n; i++)
    {
        int left = min_n - i;
        int right = min_n + i;
        for(int j = left; j <= right; j++)
        {
            vec[i][j] = 1;
        }
    }

    for(const auto &row : vec)
    {
        for(int val : row)
        {
            if(val)
            {
                std::cout << x;
            }else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}