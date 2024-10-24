#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::string s;
    std::getline(std::cin, s);

    std::stringstream l(s);
    std::vector<std::string> vec;

    std::string str;
    while(l >> str && stoi(str) != 0)
    {
        vec.push_back(str);
    }

    std::reverse(vec.begin(), vec.end());

    for(const auto &val : vec)
    {
        std::cout << stoi(val) << " ";
    }
    std::cout << std::endl;

    return 0;

}