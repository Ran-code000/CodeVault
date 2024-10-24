#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    int sum = 0;
    std::string temp;

    int x;
    int flag = 0;

    while(std::cin >> x)
    //输入写进while循环里简化代码
    {
        for(int i = 0; i < x; i++)
        {
            temp += std::to_string(flag);
        }
        flag ^= 1;
        //异或操作取代了 code1.cpp 中的奇数偶数的判别
    }

    for(int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i];
        if(i % n == n - 1) std::cout << "\n";
        //注意换行取余条件的判断
    }
    
    return 0;
}