<numeric> 头文件中包含了一系列用于执行数值操作的模板函数
这些函数包括执行累加, 求和, 内积, 部分和, 相邻差, 扫描(inclusive 和 exclusive), GCD/LCM 计算等

1. accumulate
计算给定范围内所有元素的和，也可以提供一个初始值

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};

    int sum = accumulate(v.begin(), v.end(), 0);

    cout << "Sum: " << sum << endl; 
    // 输出: Sum: 15
}


2. inner_product
计算两个范围的内积（点积）

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5, 6};
    // b.size() 要大于或等于 a.size() , 负责会出现位置的结果(比如说 -1364283718)

    int product = inner_product(a.begin(), a.end(), b.begin(), 0);

    cout << "Inner product: " << product << endl; 
    // 输出: 32
}


3. adjacent_difference
计算序列中相邻元素的差

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v = {1, 3, 6, 10};
    vector<int> diff;

    adjacent_difference(v.begin(), v.end(), back_inserter(diff));
    //在同一个向量 v 的末尾插入计算结果(agjacent_difference(v.begin(), v.end(), back_inserter(v));)
    //当 adjacent_difference 开始向 v 添加元素时，v 的大小开始增长
    //这意味着，如果在遍历过程中向容器添加更多元素，v.end() 可能会改变，导致未定义行为

    //为了避免这种问题，应该避免在使用算法处理容器时，向同一个容器追加元素
    //一个更安全的做法是使用一个单独的向量来存储结果 (比如说 diff)

    for (auto d : diff)
    {
        cout << d << " "; 
    } 
    // 输出: 1 2 3 4
    
    cout << endl;
}


4. partial_sum
计算给定范围内每个元素的部分和

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> partialSums;

    partial_sum(v.begin(), v.end(), back_inserter(partialSums));

    for (auto s : partialSums) 
    {
        cout << s << " ";
    } 
    // 输出: 1 3 6 10 15

    cout << endl;
}


5. iota
在指定范围内生成连续的递增（或递减）值

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v(5);
    iota(v.begin(), v.end(), 10); 
    // 从10开始填充连续值

    for (auto i : v) 
    {
        cout << i << " ";
    } 
    // 输出: 10 11 12 13 14

    cout << endl;


    // 试出 int 的最大边界 (2147483647)
    //-2147483648 -2147483647 -2147483646 -2147483645 -2147483644
    // 2147483643 2147483644 2147483645 2147483646 2147483647

}


6. reduce (C++17)
类似于 accumulate,但不保证顺序执行,允许并行化处理


#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};

    int sum = reduce(execution::par, v.begin(), v.end());

    cout << "Sum: " << sum << endl; // 输出取决于实现，但通常是 15
}
注意：使用 reduce 需要包含 <execution> 头文件，并确保编译器支持 C++17 或更高版本


7. inclusive_scan 和 exclusive_scan (C++17)
 
分别计算给定范围内的包含式和排他式扫描（部分和）

#include <numeric>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> inc, exc;

    inclusive_scan(v.begin(), v.end(), back_inserter(inc));
    exclusive_scan(v.begin(), v.end(), back_inserter(exc), 0);

    for (auto i : inc) 
    {
        cout << i << " ";
    } 
    // 输出: 1 3 6 10 15

    cout << endl;

    for (auto e : exc) 
    {
        cout << e << " ";
    } 
    // 输出: 0 1 3 6 10

    cout << endl;
}


8.gcd 和 lcm (C++17)
分别计算两个数的最大公约数和最小公倍数

#include <numeric>
#include <iostream>

int main() 
{
    cout << "gcd(20, 30): " << gcd(20, 30) << endl; // 输出: 10
    cout << "lcm(6, 8): " << lcm(6, 8) << endl; // 输出: 24
}
这些函数构成了 <numeric> 头文件的核心，提供了强大的数值处理能力
C++17 引入的一些函数（如 reduce, inclusive_scan, exclusive_scan, gcd 和 lcm）

