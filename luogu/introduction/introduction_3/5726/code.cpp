#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> vec(n);

    for(int i = 0; i < n; i++)
    {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());

    double ans = 0;
    for(int i = 1; i < n - 1; i++)
    {
        ans += vec[i];
    }

    std::cout << std::fixed << std::setprecision(2) << ans / (n - 2);

    return 0;
}