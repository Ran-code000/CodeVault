#include <iostream>
#include <cmath>

//最简单的代码
//逐个数字比较

char a = '0';
const int N = 1e6 + 10;
int arr[N], i = 0;

int main()
{
    char x;
    int cnt = 0;
    while(std::cin >> x)
    {
        cnt++;
        if(x == a)
        {
            arr[i]++;
        }else
        {
            arr[++i]++;
            a = x;
        }
    }

    int n = std::sqrt(cnt);
    std::cout << n << " ";

    for(int j = 0; j <= i; j++)
    {
        std::cout << arr[j] << " ";
    }

    return 0;
}