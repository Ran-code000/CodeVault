#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

int main()
{
    std::string s;
    std::getline(std::cin, s);

    if(s.find('.') != std::string::npos)
    {
        unsigned long pos = s.find('.');
        std::string str1,str2;

        str1 = s.substr(0, pos);
        std::reverse(str1.begin(), str1.end());

        str2 = s.substr(pos+1, s.size());
        std::reverse(str2.begin(), str2.end());

        unsigned long a,b;

        
        a = std::stoul(str1);
        a %= (unsigned long) std::pow(10, str1.size());

        b = std::stoul(str2);

        while(b > 10)
        {
            if(b % 10 == 0)
            {
                b /= 10;
            }else
            {
                break;
            }
        }
        std::cout << a << "." << b << std::endl;
    }else if(s.find('/') != std::string::npos)
    {
        unsigned long pos = s.find('/');
        std::string str1,str2;

        str1 = s.substr(0, pos);
        std::reverse(str1.begin(), str1.end());

        str2 = s.substr(pos+1, s.size());
        std::reverse(str2.begin(), str2.end());

        unsigned long a,b;

        a = std::stoul(str1);
        a %= (unsigned long) std::pow(10, str1.size());

        b = std::stoul(str2);
        b %= (unsigned long) std::pow(10, str2.size());
        

        std::cout << a << "/" << b << std::endl;
    }else if(s.find('%') != std::string::npos)
    {
        unsigned long pos = s.find('%');
        std::string str = s.substr(0,pos);

        std::reverse(str.begin(), str.end());

        unsigned long a;
        
        a = std::stoul(str);
        a %= (unsigned long) std::pow(10, str.size());

        std::cout << a << "%" << std::endl;
    }else
    {
        std::reverse(s.begin(), s.end());

        unsigned long a;
        a = std::stoul(s) %  (unsigned long)std::pow(10, s.size());

        std::cout << a << std::endl;

    }
    
    return 0;
}

//这些函数包括std::stoi、std::stol、std::stoll、std::stoul、std::stoull、std::stof、std::stod和std::stold，
//它们分别用于转换为int、long、long long、unsigned long、unsigned long long、float、double和long double类型的数值
//std::pow() 默认返回double 类型的数值, 如果需要用于整数需要类型转换