#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
    int ans = 0;

    std::string s;
    std::getline(std::cin,s);

    std::stringstream l(s);

    std::string str;
    std::vector<std::string> vec;
    while(l >> str)
    {
        vec.push_back(str);
    }

    for(const auto s1 : vec)
    {
        ans += s1.size();
    }

    std::cout << ans;

    return 0;
}