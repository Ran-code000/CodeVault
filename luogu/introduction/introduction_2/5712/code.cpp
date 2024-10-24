#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    std::string str = "Today, I ate ";
    str += std::to_string(n);
    str += " apple";

    if(n > 1)
    {
        str += "s.";
    }else
    {
        str += ".";
    }

    std::cout << str;
    return 0;

}