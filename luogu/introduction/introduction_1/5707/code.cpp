#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    int s, v;
    std::cin >> s >> v;

    int spendMinute = std::ceil((double)s / v) + 10;
    int spendHour = spendMinute / 60;
    spendMinute %= 60;

    int startHour = (7 - spendHour + 24) % 24; //常见写法
    int startMinute = 60 - spendMinute;
    std::cout << std::setw(2) << std::setfill('0') << startHour ;
    //注意是 std::setfill('') 不是std::fill( )， 填充的是字符
    std::cout << ":" ;
    std::cout << std::setw(2) << std::setfill('0') << startMinute ;

    return 0;
}