#include <iostream>

int arr[80];

//简单开一个数组也能做

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    for(int i = 1; i <= a; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            for(int k = 1; k <= c; k++)
            {
                int sum = i + j + k;
                arr[sum]++;
            }
        }
    }

    int max = -1;
    int ans = 0;
    for(int i = 0; i < a + b + c; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            ans = i;
        }
    }

    std::cout << ans;
    return 0;
}