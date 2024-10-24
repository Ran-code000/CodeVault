#include <iostream>
#include <utility> // 用于 std::pair<>
#include <string>
#include <vector>
#include <algorithm>

//5740 中的 node 为自定义类型，没有现有的排序规则, 需要一个 id 用来 cmp 的自定义排序
//但本题中 pair 默认按字典序排列

struct node
{
    std::string name;
    int a, b, c, sum;
}temp;

std::vector<node> vec;
std::vector<std::pair<std::string, std::string>> s;

int main()
{
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        std::cin >> temp.name >> temp.a >> temp.b >> temp.c;
        temp.sum = temp.a + temp.b + temp.c;
        vec.push_back(temp);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(abs(vec[i].a - vec[j].a) <= 5 && abs(vec[i].b - vec[j].b) <= 5 && abs(vec[i].c - vec[j].c) <= 5)
            {
                if(abs(vec[i].sum - vec[j].sum) <= 10)
                {
                    if(vec[i].name <= vec[j].name)
                    {
                        s.push_back({vec[i].name, vec[j].name});
                    }else
                    {
                        s.push_back({vec[j].name, vec[i].name});
                    }
                }
            }
        }
    }

    std::sort(s.begin(), s.end());
    //不用像 std::vector<node> 一样自定义 std::sort(s.begin(), s.end(), cmp)
    //std::pair 默认字典序排列

    for(int i = 0; i < s.size(); i++)
    {
        std::cout << s[i].first << " " << s[i].second << "\n";
    }

    return 0;
}