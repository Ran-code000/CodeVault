#include <iostream>
#include <vector>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int>(n, 0));

    int left = 0, right = n - 1;
    int begin = 0, end = n - 1;

    int ans = 1;
    int i, j;

    while(left <= right && begin <= end && ans <= n * n)
    {
        for(j = left; j <= right; j++)
        {
            i = begin;
            vec[i][j] = ans++;
        }
        begin++;

        for(i = begin; i <= end; i++)
        {
            j = right;
            vec[i][j] = ans++;
        }
        right--;

        for(j = right; j >= left; j--)
        {
            i = end;
            vec[i][j] = ans++;
        }
        end--;

        for(i = end; i >= begin; i--)
        {
            j = left;
            vec[i][j] = ans++;
        }
        left++;

    }

    i = 0, j = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            #if 0
            if(vec[i][j] < 10)
            {
                std::cout << "  " << vec[i][j];
            }else if(vec[i][j] < 100)
            {
                std::cout << " " << vec[i][j];
            }else
            {
                std::cout << vec[i][j];
            }
            #endif

            std::cout.width(3);
            std::cout << vec[i][j];
        }
        std::cout << "\n";
    }
    
    return 0;
}