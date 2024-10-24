#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    std::string str;
    std::cin >> str;

    for(int i=0; i<str.size(); i++)
    {
        str[i] = 'a'+ (str[i] - 'a' + n)%26;
        //std::cout << str[i];
    }
    std::cout << str;

    return 0;
}