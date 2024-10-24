#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>

int main()
{
    std::string s1,s;
    std::cin >> s1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::getline(std::cin,s);

    #if 0
    for(char &ch : s1)
    {
        ch = tolower(ch);
    }

    for(char &ch : s)
    {
        ch = tolower(ch);
    }
    #endif
    std::transform(s1.begin(),s1.end(),s1.begin(),[](char ch){return tolower(ch);});
    std::transform(s.begin(),s.end(),s.begin(),[](char ch){return tolower(ch);});

    std::stringstream l(s);
    std::string str;
    std::vector<std::string> vec;

    int cnt=0;

    while(l >> str)
    {
        vec.push_back(str);
    }

    for(std::string &val : vec)
    {
        if( val.size() != s1.size())
        {
            continue;
        }

        if( val == s1 )
        {
            cnt++;
        }

    }

    s1 = " " + s1 + " ";
    int index;
    index = s.find(s1) + 1;

    if(cnt > 0)
    {
        std::cout << cnt << " " << index;
    }
    else
    {
        std::cout << -1 << std::endl;
    }

    return 0;
}