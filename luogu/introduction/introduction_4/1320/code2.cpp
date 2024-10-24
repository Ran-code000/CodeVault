#include <iostream>
#include <string>
#include <cmath>
#include <vector>

//同理 cope1.cpp 用 std::string 存储输入数据的每一行。用 std::vector 把所有行捆在一起，形成矩阵
//但这个方法将矩阵展开为一个长字符串
//然后用双指针对字符串直接进行操作

int main()
{
    std::vector<std::string> vec;
    std::string s, temp;
    while(std::cin >> s && !s.empty())
    {
        vec.push_back(s);
    }
    for(const auto &str : vec)
    {
        temp += str;
    }

    std::cout << sqrt(temp.size()) << " ";

    if(temp[0] == '1') std::cout << "0 ";

    //双指针做法
    for(int i = 0; i < temp.size(); i++)
    {
        int j = i;
        while(j + 1 < temp.size() && temp[j + 1] == temp[j])
        //先排除越界情况
        {
            j++;
        }
        std::cout << j + 1 - i << " ";
        
        i = j;
    }

    return 0;
}