#include <iostream>
#include <vector>
#include <string>

//本题过程与输入顺序有关，所以不适宜用 map 或 unordered_map
//std::unordered_map不支持直接排序，因为它是一个基于哈希表的容器，设计上就是为了优化访问速度，而不是保持元素的有序性
//unordered_map的元素顺序是不确定的，而且没有提供根据索引访问的方法
//因此std::map<std::string, std::vector<int>> m 的做法无法实现按输入顺序排序,
// 尝试在向量里存放结构体, 并传入一个 id 来记录输入顺序, 使向量按输入顺序排列

//逐次输入比较，更新最大值即可

int main()
{
    int n;
    std::cin >> n;

    std::string maxName;
    std::vector<int> v(3);

    int max = -1;
    while(n--)
    {
        std::string str;
        std::cin >> str;

        int a,b,c;
        std::cin >> a >> b >> c;
        
        int sum = a + b + c;

        if(sum > max)
        {
            maxName = str;
            v[0] = a;
            v[1] = b;
            v[2] = c;
            max = sum;
        }

    }

    std::cout << maxName << " " << v[0] << " " << v[1] << " "<< v[2] << std::endl;

    return 0;
}