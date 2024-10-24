#include <iostream>
#include <map>
#include <algorithm>

/*
对于 map 容器的一些查找方法 (不同于 vector)

使用std::max_element和std::find与std::map时，需考虑std::map的迭代器访问的是一对值（即std::pair<const Key, Value>），
其中.first是键，.second是值

要使用std::max_element找到std::map中具有最大值的元素，需要提供一个比较函数，
因为默认情况下std::max_element比较的是键值对中的键，而不是值。
同样，使用std::find在std::map中查找元素时，它默认比较的是键，而不是值。

以下是如何使用std::max_element按.second（即值）排序来查找std::map中的最大元素，
以及如何使用std::find来查找特定元素的示例代码：

#include <iostream>
#include <map>
#include <algorithm>

int main() 
{
    std::map<int, int> m = {{1, 20}, {2, 25}, {3, 5}, {4, 30}};

    // 使用 std::max_element 查找具有最大值的元素
    // 注意：需要提供一个比较函数来比较键值对中的值
    auto max_it = std::max_element(m.begin(), m.end(), 
                                   [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                                       return a.second < b.second;
                                   });

    if (max_it != m.end()) 
    {
        std::cout << "最大元素是：{" << max_it->first << ", " << max_it->second << "}\n";
    }

    // 假设我们要找的值是25，我们可以这样使用 std::find_if 而不是 std::find
    // 因为 std::find 主要用于查找键而不是值
    auto it = std::find_if(m.begin(), m.end(), [](const std::pair<int, int>& pair) {
        return pair.second == 25;
    });

    if (it != m.end()) 
    {
        std::cout << "找到值为25的元素，键是：" << it->first << "\n";
    } else {
        std::cout << "找不到值为25的元素\n";
    }

    return 0;
}
这段代码首先定义了一个std::map<int, int>，然后使用std::max_element和一个自定义的比较函数来找到具有最大值的元素。
比较函数比较两个键值对的值（.second）。示例使用std::find_if（而不是std::find，因为是按值查找不是按键查找）找值为25的元素。
在这里，我们同样需要提供一个适当的比较函数。
 */

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    std::map<int, int> ans;

    for(int i = 1; i <= a; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            for(int k = 1; k <= c; k++)
            {
                int sum = 0;
                sum += i + j + k;
                ans[sum]++;
            }
        }
    }

    for(const auto &it : ans)
    {
        auto max_it = std::max_element(ans.begin(), ans.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){return a.second < b.second ;});
        if(max_it != ans.end())
        {
            std::cout << max_it->first;
            break;
        }
    }

    return 0;
}


