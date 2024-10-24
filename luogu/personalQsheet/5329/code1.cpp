#include <iostream>
#include <string>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;

    std::vector<int> ans(n);
    int l = 0, r = n - 1, tag = 0;
    for(int i = 1; i < n; i++)
    {
        if(s[i] > s[i - 1])
        {
            for(int j = i - 1; j >= tag; j--)
            {
                ans[r--] = j + 1;
            }
            tag = i;
        }
        if(s[i] < s[i - 1])
        {
            for(int j = tag; j < i; j++)
            {
                ans[l++] = j + 1;
            }
            tag = i;
        }
    }
    for(int i = tag; i < n; i++)
    {
        ans[l++] = i + 1;
    }
    for(int val : ans)
    {
        std::cout << val << " ";
    }


    return 0;
}