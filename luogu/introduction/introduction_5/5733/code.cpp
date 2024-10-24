#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    
    int length = str.size();

    for(int i=0; i<length; i++)
    {
        //str[i] = toupper(str[i]);
        std::cout << (char)toupper(str[i]);
        //若直接std::cout << toupper(str[i]);输出的是字符的ascall码
        //要么存回原字符串，要么强制类型转换
    }
    
    return 0;
}