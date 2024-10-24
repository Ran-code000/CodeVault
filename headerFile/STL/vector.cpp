<vector> 头文件是 C++ 标准库的一部分，它提供了 std::vector 容器类的定义。
std::vector 是一个序列容器，可以存储元素的动态数组，允许随机访问，可以快速在尾部插入和删除元素，且能自动管理存储空间。

常用的 std::vector 成员函数和操作：

1.构造函数:

vector()：创建一个空的 std::vector。
vector(size_type n, const value_type& val)：创建一个包含 n 个元素的 std::vector,每个元素的值都是 val。
vector(size_type n)：创建一个包含 n 个默认初始化元素的 std::vector。
vector(InputIterator first, InputIterator last)：通过迭代器范围 [first, last) 构造 std::vector。
vector(const vector& x)：拷贝构造函数。
vector(vector&& x)：移动构造函数。
vector(initializer_list<value_type> il)：通过初始化列表构造 std::vector。

2.赋值操作:

operator=：给 std::vector 赋值。
assign(size_type n, const value_type& val)：将 std::vector 的内容替换为 n 个 val 的拷贝。
assign(InputIterator first, InputIterator last)：通过迭代器范围 [first, last) 替换 std::vector 的内容。
assign(initializer_list<value_type> il)：通过初始化列表替换 std::vector 的内容。

3.元素访问:

at(size_type n)：访问指定元素，并进行越界检查。
operator[]：访问指定元素。
front()：访问第一个元素。
back()：访问最后一个元素。
data()：返回指向内存中第一个元素的指针。

4.迭代器:

begin() / cbegin()：返回指向第一个元素的迭代器。
end() / cend()：返回指向最后一个元素之后的迭代器。
rbegin() / crbegin()：返回到第一个元素的反向迭代器。
rend() / crend()：返回到最后一个元素之后的反向迭代器。

5.容量:

size()：返回 std::vector 中元素的个数。
max_size()：返回 std::vector 可以容纳的最大元素数。
resize(size_type n, value_type val = value_type())：更改容器大小。
capacity()：返回 std::vector 在重新分配之前可以容纳的元素数量。
empty()：检查 std::vector 是否为空。
reserve(size_type n)：请求改变 std::vector 的容量。
shrink_to_fit()：尝试减少容量以适应大小。

6.修改操作:

push_back(const value_type& val)：在 std::vector 的末尾添加一个新元素。
push_back(value_type&& val)：移动版本的 push_back。
pop_back()：移除末尾元素。
insert(iterator position, const value_type& val)：在指定位置插入元素。
insert(iterator position, size_type n, const value_type& val)：在指定位置插入 n 个元素。
insert(iterator position, InputIterator first, InputIterator last)：从范围 [first, last) 插入元素。
insert(iterator position, initializer_list<value_type> il)：从初始化列表插入元素。
erase(iterator position)：移除指定位置的元素。
erase(iterator first, iterator last)：移除迭代器范围 [first, last) 内的所有元素。
swap(vector& x)：与另一个 std::vector 交换内容。
clear():移除所有元素,容器大小变为0。

特殊的非成员函数:

std::swap(vector<T>& x, vector<T>& y)：交换两个 std::vector 的内容。

示例代码：

#include <vector>
#include <iostream>

int main() {
    // 构造函数
    std::vector<int> v1; // 空的vector
    std::vector<int> v2(5, 10); // 大小为5，初始值为10的vector
    std::vector<int> v3(v2.begin(), v2.end()); // 从v2拷贝元素的vector
    std::vector<int> v4(v2); // v2的复制
    std::vector<int> v4(v3); // 使用v3的副本创建v4
    std::vector<int> v5 = {1, 2, 3, 4, 5}; // 使用初始化列表创建一个向量

    
    // 赋值操作
    std::vector<int> v5;
    v5 = v4; // 使用赋值运算符
    v5.assign(7, 100); // 将v5的内容替换为7个值为100的元素
    

    // 元素访问
    int firstElement = v5[0]; // 访问第一个元素
    int secondElement = v5.at(1); // 访问第二个元素，如果索引越界会抛出 std::out_of_range获取第一个和最后一个元素：
    int first = v5.front(); // 获取第一个元素
    int last = v5.back(); // 获取最后一个元素

    
    // 迭代器
    for (auto it = v5.begin(); it != v5.end(); ++it)   
    {
        std::cout << *it << ' ';
    }

    for (int& value : v5) 
    {
    std::cout << value << std::endl;
    }

    std::cout << std::endl;

    // 容量
    if (!v5.empty()) { // 检查非空
        std::cout << "Size of v5: " << v5.size() << std::endl;
    }
    v2.resize(15); // 将v2的大小改变为15个元素
    size_t capacity = v2.capacity(); // 获取v2的容量
    v2.reserve(20); // 将v2的容量增加到至少20

    // 修改操作
    v5.push_back(200); // 在尾部添加元素
    v5.pop_back(); // 移除尾部元素
    v5.insert(v5.begin(), 300); // 在头部插入元素
    v5.erase(v5.begin()); // 移除头部元素
    v5.clear(); // 清空所有元素

    //向量排序（需要包含 <algorithm> 头文件）：
    #include <algorithm>
    // ...
    std::sort(v5.begin(), v5.end()); // 将v5的元素排序
    
    //找到向量中的元素（同样需要 <algorithm>）：
    auto it = std::find(v5.begin(), v5.end(), 3); // 找到值为3的元素的迭代器


    return 0;
    }
    记得包含 <vector> 头文件，并且在大多数情况下，使用命名空间 std。

    
    
    tips:
    resize 改变向量的大小（即元素的数量），可能会创建新的元素或销毁现有元素；
    而 reserve 只是确保向量有足够的容量来存储指定数量的元素，避免频繁的内存分配，但不会改变向量的大小。

#include <vector>
#include <iostream>

int main() {
    std::vector<int> v {1, 2, 3, 4, 5};

    // 增大向量的大小到10，新增的元素初始化为0
    v.resize(10);
    std::cout << "After resize up to 10: ";
    for (int n : v) std::cout << n << " "; // 输出: 1 2 3 4 5 0 0 0 0 0
    std::cout << "\n";

    // 减小向量的大小到3，多余的元素会被销毁
    v.resize(3);
    std::cout << "After resize down to 3: ";
    for (int n : v) std::cout << n << " "; // 输出: 1 2 3
    std::cout << "\n";

    return 0;
}


#include <vector>
#include <iostream>

int main() {
    std::vector<int> v;

    // 初始时，向量可能有一个小的容量或者没有分配内存
    std::cout << "Initial capacity: " << v.capacity() << "\n";

    // 增加向量的容量到100，但不添加新元素
    v.reserve(100);
    std::cout << "Capacity after reserve: " << v.capacity() << "\n"; // 输出: 至少100，取决于实现

    // 实际向量的大小仍然为0，因为没有添加新元素
    std::cout << "Size after reserve: " << v.size() << "\n"; // 输出: 0

    return 0;
}




其他用法 :
1.emplace_back()
emplace_back() 方法用来在 std::vector 的末尾直接构造一个新元素。它可以接受任意数量和类型的参数，
并将这些参数传递给元素类型的构造函数。这比先构造一个临时对象再插入到向量中（使用 push_back()）更高效。

#include <vector>
#include <string>

int main() {
    std::vector<std::string> v;

    // 使用 push_back 添加字符串
    v.push_back(std::string("Hello"));

    // 使用 emplace_back 直接在向量的末尾构造字符串
    v.emplace_back("World"); // 不需要构造临时 std::string 对象

    return 0;
}

2.emplace()
emplace() 方法类似于 emplace_back()，但它允许你在 std::vector 的任意位置直接构造新元素。
你需要传递一个指向插入位置的迭代器，紧接着是构造新元素所需的参数。

#include <vector>

int main() {
    std::vector<int> v{1, 2, 4, 5};

    // 在第三个元素位置构造一个新元素 3
    v.emplace(v.begin() + 2, 3); // v 现在是 {1, 2, 3, 4, 5}

    return 0;
}

3.swap()
swap() 方法交换两个同类型 std::vector 的内容。这是个非常高效的操作，通常只涉及指针的交换。

#include <vector>
#include <algorithm> // 为了 std::swap

int main() {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{4, 5, 6};

    // 交换 v1 和 v2 的内容
    v1.swap(v2); // 或者 std::swap(v1, v2);

    return 0;
}

4.data()
data() 方法返回一个指向 std::vector 存储的第一个元素的指针。这可以用来与需要原始数组的 C 函数接口进行交互。

#include <vector>
#include <cstring> // 为了使用 memcpy

int main() {
    std::vector<char> v{'H', 'e', 'l', 'l', 'o'};
    char buffer[6];

    // 将 vector 的内容复制到字符数组
    std::memcpy(buffer, v.data(), v.size());
    buffer[5] = '\0'; // 添加空字符作为字符串的末尾

    return 0;
}

5.assign()
assign() 方法用来替换 std::vector 中的所有元素。它可以填充向量具有特定数量的拷贝一个给定值，或者用一个元素范围或初始化列表的内容来替换当前内容。

#include <vector>

int main() {
    std::vector<int> v;

    // 用 5 个 2 来填充向量
    v.assign(5, 2); // v 现在是 {2, 2, 2, 2, 2}

    // 用初始化列表的内容替换向量的内容
    v.assign({1, 2, 3}); // v 现在是 {1, 2, 3}

    return 0;
}
每个这些方法都有不同的用途，并且是 std::vector 提供的灵活性和强大功能的一部分。需要注意的是，对于复杂的对象类型，合理使用 emplace 类方法可以避免不必要的对象拷贝，从而提升性能。而 swap 在需要交换两个向量的内容时非常快，因为它不进行元素级别的拷贝。data() 方法提供了一个方便的接口，使得向量可以与期望使用原始数组的 C API 兼容。最后，assign 方法则是用来批量替换向量中的元素。



