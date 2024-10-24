#include <iostream>
#include <string>

int main()
{
    std::string str1,str2;

    std::cin >> str1 >> str2;

    unsigned long ans1 = 1, ans2 = 1;

    for(int i = 0; i < str1.size(); i++)
    {
        ans1 *= (str1[i] - 'A' + 1);
    }

    for(int i = 0; i < str2.size(); i++)
    {
        ans2 *= (str2[i] - 'A' + 1);
    }

    if((ans1 % 47) == (ans2 % 47))
    {
        std::cout << "GO" << std::endl;
    }else
    {
        std::cout << "STAY" << std::endl;
    }

    return 0;
    
}