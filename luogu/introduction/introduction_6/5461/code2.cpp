#include <iostream>
#include <vector>

//观察数据，用杨辉三角的思想，异或来做

int main()
{   
    int num;
    std::cin >> num;

    int size = 1 << num;

    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

    for(int j = size - 1; j < size; j++)
    {
        for(int i = 0; i < size; i++)
        {
            matrix[i][j] = 1;
        }
    }

    for(int i = 1; i < size; i++)
    {
        for(int j = 0; j < size - 1; j++)
        {
            matrix[i][j] = matrix[i - 1][j] ^ matrix[i - 1][j + 1];
        }
    }

    for(const auto row : matrix)
    {
        for(const int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}