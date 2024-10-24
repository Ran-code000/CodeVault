#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cin >> str;

    for(int i = str.length() - 1; i >= 0; i--)
    {
        std::cout << str[i];
    }
    return 0;
}