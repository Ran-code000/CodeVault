#include <iostream>
#include <map>
#include <algorithm>

int main()
{
    char c;

    std::map<char,int> m;

    while(std::cin >> c)
    {
        if( c >= 'A' && c <= 'Z')
        {
            ++m[c];
        }

    }

    int max = 0;

    auto max_it = std::max_element(m.begin(), m.end(), 
    [](const std::pair<char, int> &a, const std::pair<char, int> &b){return a.second < b.second ;});
    max = max_it->second;

    /*for(auto &i : m)
    {
        max = std::max(max,i.second);
    }*/



    for(int i=0; i<max; i++)
    {
        for(int j=0; j<26; j++)
        {
            if( i >= max-m[j+'A'] )
            {
                std::cout << "*";
            }else
            {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }

    for(auto &i : m)
    {
        std::cout << i.first << " ";
    }

    return 0;
}