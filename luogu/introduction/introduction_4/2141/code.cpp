#include <iostream>
#include <vector>
#include <algorithm>

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

    int ans = 0;
    int i, j, k;
    
    for(i = n - 1; i >= 2; i--)
    { 
        j = 0;
        k = i - 1;
        //排序后的向量，用双指针做法效率更高
        while(j < k)
        {
            if(vec[i] == vec[j] + vec[k])
            {
                j++;
                k--;
                ans++;
                break;
                //找到一种即可
            }else if (vec[i] < vec[j] + vec[k])
            {
                k--;
            }else
            {
                j++;
            }
            
        }
    }
    
    std::cout << ans;

    return 0;
    
}