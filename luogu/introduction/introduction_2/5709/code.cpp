#include <iostream>
#include <cmath>

int main()
{
    int m, t, s;
    std::cin >> m >> t >> s;
    if(t == 0)
    //对除数等于 0 进行特判
    {
        std::cout << 0;
        return 0;
    }

    std::cout << std::max(m - ceil((double)s / t), 0.0);
    //包含 <cmath> 头文件, 来调用 c 中的向上取整函数 ceil
    
    return 0;
}