#include <iostream>
#include <vector>
#include <string>

//用 std::string 存储输入数据的每一行。用 std::vector 把所有行捆在一起，形成矩阵
//直接对矩阵进行操作

int main()
{
    std::vector<std::string> vec;
    std::string str;
    
    while(std::getline(std::cin, str) && !str.empty())
    {
        vec.push_back(str);
    }
    std::cout << vec.size() << " ";

    int cnt = 0;
    char currentch = '0'; //当前值
    for(const auto &row : vec)
    {
        for(char val : row)
        {
            if(val == currentch)
            {
                cnt++;
            }else
            {
                std::cout << cnt << " ";
                cnt = 1;
                currentch = val;
            }
        }
    }

    std::cout << cnt << " ";
    
    return 0;
}