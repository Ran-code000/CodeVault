#include <iostream>
#include <cctype>

int main()
{
    char x;
    std::cin >> x;

    //x = std::toupper(x);
    //std::cout << x;

    x -= 'a' - 'A';
    std::cout << (char)x;

    //不能直接 std::cout << std::toupper(x);
    //输出的是字符的ascall码

    return 0;
}