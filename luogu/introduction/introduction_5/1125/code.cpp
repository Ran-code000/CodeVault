#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <climits>
#include <algorithm>

bool isPrime(int num)
{
    if(num <= 1)
    {
        return false;
    }

    if(num == 2)
    {
        return true;
    }

    if(num % 2 == 0)
    {
        return false;
    }

    for(int i=3; i<=sqrt(num); i+=2)
    {
        if(num % i == 0)
        {
            return false;
        }
    }

     return true;
}

int main()
{
    std::string str;
    std::cin >> str;

    std::map<char,int> m;

    for(char &ch : str)
    {
        ++m[ch];
    }

    
    int max = -1;
    int min = INT_MAX;
    for(const auto &it : m)
    {
        max = std::max(max,it.second);
        min = std::min(min,it.second);
    }

    if(isPrime(max - min))
    {
        std::cout << "Lucky Word" << '\n';
    }else
    {
        std::cout << "No Answer" << "\n";
    }

    std::cout << max - min << std::endl;

    return 0;
}