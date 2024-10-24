#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec1(7);
    int ans[7] = {0};

    int n;
    std::cin >> n;

    for(int i = 0; i < 7; i++)
    {
        int a;
        std::cin >> a;
        vec1.push_back(a);
    }

    while(n--)
    {
        int cnt = 0;
        for(int i = 0; i < 7; i++)
        {
            int a;
            std::cin >> a;

            auto it = std::find(vec1.begin(), vec1.end(), a);
            if(it != vec1.end()) cnt++;
            
        }
        ans[7 - cnt]++;
        //若用vector<int> ans， 没办法直接用下标访问
    }

    for(const auto &val : ans)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}