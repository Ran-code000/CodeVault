#include <iostream>
#include <string>

int main()
{
    int arr[15] = {0};

    int n, m;
    std::cin >> n >> m;

    for(int i = n; i <= m; i++)
    {
        std::string str;
        str = std::to_string(i);
        
        for(char j = 0; j < str.size(); j++)
        {
            arr[str[j] - '0']++;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;

}