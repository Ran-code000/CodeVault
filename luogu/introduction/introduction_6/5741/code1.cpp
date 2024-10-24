#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>

//本题不同于5740, 需要将每一组数据记录下来, 可用到 map (map里也可以用向量)

int main()
{
    int n;
    std::cin >> n;

    std::string str;
    std::map<std::string, std::vector<int>> m;

    while(n--)
    {
        std::cin >> str;
        std::vector<int> v(3);

        std::cin >> v[0] >> v[1] >> v[2];
        m[str] = v;

    }

    for(auto it1 = m.begin(); it1 !=m.end(); it1++)
    {
        auto it2 = it1;
        it2++;
        //auto it2 = m.begin() + 1; 写法错误，map,unordered_map 不支持这种写法

        for(; it2 !=m.end(); it2++)
        {
            int sum1 = std::accumulate(it1->second.begin(), it1->second.end(), 0);
            int sum2 = std::accumulate(it2->second.begin(), it2->second.end(), 0);
            if(abs(it1->second[0] - it2->second[0]) <= 5 && abs(it1->second[1] - it2->second[1]) <= 5 
            && abs(it1->second[2] - it2->second[2]) <= 5 && abs(sum1 - sum2) <= 10)
            {
                std::cout << it1->first << " " << it2->first << std::endl;
            }
        } 
    }
    return 0;

}

/*
map和unordered_map是关联容器，它们内部的元素是按照键值对来存储的。这些容器不支持随机访问迭代器，
所以不能使用像it2 = m.begin() + 1这样的操作来访问元素，因为+运算符对于它们的迭代器来说是未定义的。

可以使用随机访问的容器：比如vector、deque和array，支持it + n这样的操作。

在map和unordered_map中实现相似操作：
如果想要访问map或unordered_map中的下一个元素，应该使用++it来递增迭代器。

例如，要让迭代器指向第二个元素，可以
auto it = m.begin();
if(it != m.end()) ++it; // 确保不是空的map，然后移动到第二个元素（如果有的话）

这种方法是适用于所有类型的标准库容器的通用方法，包括那些不支持随机访问的容器。
*/