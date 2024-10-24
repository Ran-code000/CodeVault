#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec(10);
    for(int i = 0; i < 10; i++)
    {
        std::cin >> vec[i];
    }

    int n;
    std::cin >> n;

    int ans = 0;
    for(const int &val : vec)
    {
        if(n + 30 >= val) ans++;
    }

    std::cout << ans;
    return 0;
}