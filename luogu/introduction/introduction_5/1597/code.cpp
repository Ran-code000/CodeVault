#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>

int main()
{
    std::string str;
    std::cin >> str;

    std::map<char, int> m = {{'a', 0}, {'b', 0}, {'c', 0}};

    std::string ss = ":=";
    int pos = 0;

    while((pos = str.find(ss, pos)) != std::string::npos)
    {
        char left = str[pos - 1];
        char right = str[pos + 2];

        if(isdigit(right))
        {
            m[left] = right - '0';
            
        }else if(isalpha(right))
        {
            m[left] = m[right];
        }

        pos = str.find(";", pos) + 1;
        
    }


    for(auto &it : m)
    {
        
        std::cout << it.second << " ";
    }
    std::cout << std::endl;

    return 0;

}

/*
原想法思路及代码：
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>

int main()
{
    std::string str;
    std::cin >> str;

    std::map<char, int> m = {{'a', 10}, {'b', 10}, {'c', 10}};

    std::string ss = ":=";
    int pos = 0;

    while((pos = str.find(ss, pos)) != std::string::npos)
    {
        if(isdigit(str[pos + 2]))
        {
            m[str[pos - 1]] = str[pos + 2] - '0';
        }else if(isalpha(str[pos + 2]) && m[str[pos + 2]] < 10)
        {
            m[str[pos - 1]] = m[str[pos + 2]];
        }else if(isalpha(str[pos + 2]) && m[str[pos + 2]] == 10)
        {
            if(m[str[pos -1]] == 10)
            {
                m[str[pos - 1]] = 0;
            }else
            {
                continue;
            }
        }

        pos = str.find(";", pos) + 1;
        
    }

    for(auto &it : m)
    {
        std::cout << it.second << " ";
    }
    std::cout << std::endl;

    return 0;

}

//其实无需检查右边变量是否赋值过(判断与0的大小), 只需将 map 初始化为 0 就好
//注意map,str下标的区分, 写的难读, 可将 for 循环中 str 的下标对应的值提取出来更为简洁 
//str的值又对应着 map 的下标

*/