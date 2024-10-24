#include <iostream>
#include <map>

int main()
{
    int a[15] = {0};
    std::map<int, int> m;
    
    int n;
    std::cin >> n;

    for(int i = 0; i < 7; i++)
    {
        int x;
        std::cin >> x;
        m[x]++;
    }

    while(n--)
    {
        int cnt = 0;
        for(int i = 0; i < 7; i++)
        {
            int x;
            std::cin >> x;
            if(m[x]) cnt++;
            //用 map 来代替 std::find 的实现
        }
        a[7 - cnt]++;
    }

    for(int i = 0; i < 7; i++)
    {
        std::cout << a[i] << " ";
    }
    return 0;
}