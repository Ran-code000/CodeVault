#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

int main()
{
    int m, n;
    std::cin >> n >> m;

    std::vector<int> v1;
    std::vector<double> v2;

    v1.reserve(m);
    v2.reserve(n);

    /*
    使用push_back添加元素与reserve为容器预留空间是两个不同的操作，它们服务于不同的目的。

    push_back方法：
    向容器的末尾添加一个新元素。如果容器的当前大小小于容量，push_back直接在容器末尾添加新元素。
    如果大小等于容量，容器会自动增加其容量（通常是当前容量的两倍），然后添加新元素。

    reserve方法：
    仅为容器预留空间，但不实际创建元素。这意味着它只影响容器的容量，而不影响其大小。
    reserve主要用于优化性能，减少在添加元素时可能发生的多次内存分配。

    */
    
    for(int i = 0; i < n; i++)
    {   
        v1.clear();
        
        for(int j = 0; j < m; j++)
        {
            int num;
            std::cin >> num;
            v1.push_back(num);
            //std::cin >> v1[j];
            //v1[j]或v2[i]这种方式访问元素时，是在尝试访问容器中的现有元素。
            //如果容器的大小小于j或i，这种访问是越界的，会导致未定义行为，通常是运行时错误
        }
        std::sort(v1.begin(), v1.end());

        double sum = (std::accumulate(v1.begin() + 1, v1.end() - 1, 0.0)) / (v1.size() - 2) ;
        //如果两个操作数都是整数，则执行整数除法，结果也是整数，小数部分会被丢弃。
        //如果至少有一个操作数是浮点数,则执行浮点除法,结果是浮点数,保留小数部分。因此用0.0作为std::accumulate的初始值

        v2.push_back(sum);
    }

    auto max = std::max_element(v2.begin(), v2.end());
    std::cout << std::fixed << std::setprecision(2) << *max;

    return 0;
}