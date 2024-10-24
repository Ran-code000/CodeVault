#include <iostream>
#include <cmath>

//不需要真的求子集，找规律
//但有关求子集的实现方法在 code2.cpp

int main()
{
    int a;
    long long sum = 0;
    int cnt = 0;

    while(std::cin >> a)
    {
        sum += a;
        cnt++;
    }
    std::cout << sum * (long long)pow(2, cnt - 1) << std::endl;
    //pow 默认输出的为 double

    return 0;
}