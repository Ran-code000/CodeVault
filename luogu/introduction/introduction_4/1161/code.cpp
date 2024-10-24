#include <iostream>
#include <algorithm>

const int N = 2 * 1e6 + 10;
int arr[N] = {0};

int main()
{
    int n;
    std::cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        double a;
        int t;
        std::cin >> a >> t;

        for(int j = 1; j <= t; j++)
        {
            arr[(int)(a * j)] ^= 1;
            //(int)强制转换后不是四舍五入， 是保留整数部分
            //异或操作，异或奇数次状态改变，偶数次状态不变

            //~arr[(int)(a * j)] 写法不对实际上没有对arr数组的内容进行修改。
            //位反操作符~对其操作数进行位反转操作，但结果没有赋值给任何变量，因此arr数组的内容保持不变
        }
    }

    for(int i = 0; i < N; i++)
    {
        if(arr[i])
        {
            std::cout << i;
            break;
        }
    }

    return 0;
}