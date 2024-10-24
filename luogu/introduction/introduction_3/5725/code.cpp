#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int> (n, 0));
    int ans = 1;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            vec[i][j] = ans++;
        }
    }
    for(const auto &row : vec)
    {
        for(int val : row)
        {
            std::cout << std::setw(2) << std::setfill('0') << val;
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::vector<std::vector<std::string>> v(n, std::vector<std::string>(n, "0"));
    ans = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = n - 1 - i; j < n; j++)
        {
            v[i][j] = std::to_string(ans++);
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {   
            if(v[i][j] == "0")
            {
                std::cout << "  ";
                continue;
            }
            std::cout << std::setw(2) << std::setfill('0') << v[i][j];
        }
        std::cout << "\n";
    }

    

    return 0;
}