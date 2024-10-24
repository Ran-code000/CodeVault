#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

int main()
{
    std::string s;
    std::getline(std::cin,s);

    std::stringstream l(s);
    std::string str;
    std::vector<std::string> vec;
    std::map<char,int> m;

    m = {{'a',1},{'b',2},{'c',3},
    {'d',1},{'e',2},{'f',3},
    {'g',1},{'h',2},{'i',3},
    {'j',1},{'k',2},{'l',3},
    {'m',1},{'n',2},{'o',3},
    {'p',1},{'q',2},{'r',3},{'s',4},
    {'t',1},{'u',2},{'v',3},
    {'w',1},{'x',2},{'y',3},{'z',4}};

    int sum = 0;

    while(l >> str)
    {
        vec.push_back(str);
    }

    for(std::string &val : vec)
    {
        for(char &ch : val)
        {
            sum += m[ch];
        }
    }

    int count = std::count(s.begin(),s.end(),' ');
    //count = std::count(s.data(),s.data()+s.size(),' ');
    count += std::count(s.begin(),s.end()+s.size(),'\n');

    sum += count;
    
    std::cout << sum << std::endl;

    return 0;
}


/*
data() 是 std::string 和容器（如 std::vector, std::array 等）中的成员函数，用于获取指向其内部数据的指针。
对于 std::string，data() 返回一个指向以null终止的字符数组的指针（从 C++11 开始保证），允许读取字符串的内容。

1.std::string 中的 data()

#include <iostream>
#include <string>

int main() 
{
    std::string str = "Hello, World!";
    const char* cstr = str.data();

    std::cout << cstr << std::endl; 
    // 输出: Hello, World!

    return 0;
}

2.std::vector 中的 data()

#include <iostream>
#include <vector>

int main() 
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int* ptr = vec.data();

    for (size_t i = 0; i < vec.size(); ++i) 
    {
        std::cout << *(ptr + i) << " "; // 输出: 1 2 3 4 5
    }
    return 0;
}
*/

