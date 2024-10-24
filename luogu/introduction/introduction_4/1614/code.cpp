#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> vec, ans;
    vec.reserve(n);
    ans.reserve(n - 2);

    for(int i = 0; i < n; i++)
    {
        int a;
        std::cin >> a;
        vec.push_back(a);
    }

    for(int i = 0; i < n - m + 1; i++)
    {
        int sum = 0;
        for(int j = i; j < i + m; j++)
        {
            sum += vec[j];
        }
        ans.push_back(sum);
    }

    std::sort(ans.begin(), ans.end());

    std::cout << ans[0];

    return 0;
}