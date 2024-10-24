#include <iostream>

const int N = 1e5 + 10;
int a[N];

int main()
{
    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    for(int i = 0; i < n; i++)
    {
        int cnt = 0;
        //每次计数要清零
        for(int j = 0; j < i; j++)
        {
            if(a[j] < a[i])
            {
                cnt++;
            }
        }
        std::cout << cnt << " ";
    }
}