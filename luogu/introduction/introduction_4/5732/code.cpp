#include <iostream>
#include <vector>
int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int>(n, 1));

    for(int i = 2; i < n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            vec[i][j] = vec[i - 1][j - 1] + vec[i - 1][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i + 1; j++)
        {
            std::cout << vec[i][j] << " ";
        }
        std::cout << "\n";
    }


    return 0;
}