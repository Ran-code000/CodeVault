# STL 全析：6 大组件 + 13 个头文件

## 概念

    STL（Standard Template Library） 是 C++ 标准库的一部分，它提供了一组模板类和函数，用于支持常见的数据结构和算法

## STL 6大组件

### 一、容器 Container 
    
各种存放数据的数据结构： 

1. ***序列容器（Sequence Containers）***：元素按顺序存储，可以随机访问

详见[](#一序列容器)

    （1）vector：动态数组

    （2）list：双向链表

    （3）deque：双端队列

    （4）array：固定大小的数组（C++11 引入）

    （5）forward_list：单向链表（C++11 引入）
    
2. ***关联容器（Associative Containers）***：元素根据某个特定规则（如键值对）进行排序

详见[](#三关联容器)

    （1）set：集合，存储唯一元素，自动排序

    （2）map：映射（字典），存储键值对，按键排序

    （3）multiset：多重集合，可以存储重复元素

    （4）multimap：多重映射，可以存储具有相同键的多个值

3. ***无序容器（Unordered Containers）（C++11 引入）***

```txt
（1）unordered_set：无序集合

（2）unordered_map：无序映射

（3）unordered_multiset：无序多重集合

（4）unordered_multimap：无序多重映射

```

---

### 二、算法 Algorithm 

详见[](#四算法)

1. 排序：
  
    sort，stable_sort

2. 查找：
  
    find，binary_search

3. 合并：

    merge

4. 去重：

    unique

5. 操作与比较：

    equal，reverse

6. 数值算法（需要头文件 numeric）

    gcd， lcm 等

这些算法是与容器分离的，可以独立于容器实现，通过迭代器与容器进行交互

---

### 三、迭代器 Iterator 

详见[](#六迭代器)

***迭代器是 STL 的核心，容器与算法之间通过迭代器进行关联，提供对容器元素的统一访问方式***

迭代器像指针一样工作，但比指针更加灵活，支持不同类型的容器，其 ***本质是泛型指针***

常见的迭代器类型：

      1. 输入迭代器：用于读取容器中的元素。

      2. 输出迭代器：用于写入容器中的元素。

      3. 前向迭代器：支持单向遍历。

      4. 双向迭代器：支持双向遍历。

      5. 随机访问迭代器：支持通过下标访问容器元素，具有与数组类似的访问方式

---

### 四、仿函数 Function Object （函数对象（Functors））

1. 定义：仿函数通过定义 operator() 成员函数,将一个类的对象变成可调用的函数对象

        函数对象与算法配合使用，提供自定义的操作（如比较器、加法器等）

  例如，sort 可以使用自定义的比较函数对象来决定如何排序：

```cpp
struct Compare 
{
    bool operator()(int a, int b) 
    {
        return a < b;
    }
};

vector<int> v = {4, 1, 3, 2};
sort(v.begin(), v.end(), Compare());
```

---

### 五、适配器 Adaptor 

详见[](#二容器适配器)

用于修饰容器，仿函数， 迭代器接口

1. 容器适配器：

    （1）queue（队列）

    （2）priority_queue（优先队列）

    （3）stack（栈）

2. 迭代器适配器：

    （1）reverse_iterator（反向迭代器）

    （2）back_insert_iterator（后插入迭代器）(工厂函数: back_inserter())

    （3）front_insert_iterator（前插入迭代器）(工厂函数: front_inserter())

    （4）insert_iterator（插入迭代器）(工厂函数: inserter())

3. 函数适配器：

    （1）bind（在 C++11 中替代了旧的 bind1st 和 bind2nd）

    （2）mem_fn（成员函数适配器）

    （3）not1，not2（否定谓词）

---

### 六、空间配制器 Allocator 

负责空间配置与管理

1. allocator

    标准库默认的配置器

2. __gnu_cxx::__pool_alloc

    GCC 特有的内存池配置器

3. boost::pool_allocator

    Boost 库提供的内存池配置器

4. pmr::polymorphic_allocator (C++17)

    多态分配器，可以在运行时选择不同的内存资源

5. 自定义配置器

    用户可以根据需要实现自己的配置器，只要满足 Allocator 的要求

---

## 13 个头文件

---

### 一、序列容器

#### 1. vector

    vector 是一个序列容器，可以存储元素的动态数组，允许随机访问，可以快速在尾部插入和删除元素，且能自动管理存储空间。

##### 常用的 vector 成员函数和操作

（1）构造函数

    vector()：创建一个空的 vector

    vector(size_type n, const value_type& val)：创建一个包含 n 个元素的 vector,每个元素的值都是 val

    vector(size_type n)：创建一个包含 n 个默认初始化元素的 vector

    vector(InputIterator first, InputIterator last)：通过迭代器范围 [first, last) 构造 vector

    vector(const vector& x)：拷贝构造函数

    vector(vector&& x)：移动构造函数

    vector(initializer_list<value_type> il)：通过初始化列表构造 vector

（2）赋值操作:

    operator=：给 vector 赋值

    assign(size_type n, const value_type& val)：将 vector 的内容替换为 n 个 val 的拷贝

    assign(InputIterator first, InputIterator last)：通过迭代器范围 [first, last) 替换 vector 的内容

    assign(initializer_list<value_type> il)：通过初始化列表替换 vector 的内容

（3）元素访问:

    at(size_type n)：访问指定元素，并进行越界检查

    operator[]：访问指定元素

    front()：访问第一个元素

    back()：访问最后一个元素

    data()：返回指向内存中第一个元素的指针

（4）迭代器:

    begin() / cbegin()：返回指向第一个元素的迭代器

    end() / cend()：返回指向最后一个元素之后的迭代器

    rbegin() / crbegin()：返回到第一个元素的反向迭代器

    rend() / crend()：返回到最后一个元素之后的反向迭代器

（5）容量:

    size()：返回 vector 中元素的个数

    max_size()：返回 vector 可以容纳的最大元素数

    resize(size_type n, value_type val = value_type())：更改容器大小

    capacity()：返回 vector 在重新分配之前可以容纳的元素数量

    empty()：检查 vector 是否为空

    reserve(size_type n)：请求改变 vector 的容量

    shrink_to_fit()：尝试减少容量以适应大小

（6）修改操作:

    push_back(const value_type& val)：在 vector 的末尾添加一个新元素

    push_back(value_type&& val)：移动版本的 push_back

    pop_back()：移除末尾元素

    insert(iterator position, const value_type& val)：在指定位置插入元素

    insert(iterator position, size_type n, const value_type& val)：在指定位置插入 n 个元素

    insert(iterator position, InputIterator first, InputIterator last)：从范围 [first, last) 插入元素

    insert(iterator position, initializer_list<value_type> il)：从初始化列表插入元素

    erase(iterator position)：移除指定位置的元素

    erase(iterator first, iterator last)：移除迭代器范围 [first, last) 内的所有元素

    swap(vector& x)：与另一个 vector 交换内容

    clear():移除所有元素,容器大小变为0

（7）特殊的非成员函数:

    swap(vector<T>& x, vector<T>& y)：交换两个 vector 的内容


###### 示例代码 1

```cpp

#include <vector>
#include <iostream>

using namespace std;

int main()
{
  // 构造函数
  vector<int> v1;                       // 空的vector
  vector<int> v2(5, 10);                // 大小为5，初始值为10的vector
  vector<int> v3(v2.begin(), v2.end()); // 从v2拷贝元素的vector
  vector<int> v4(v2);                   // v2的复制
  vector<int> v4(v3);                   // 使用v3的副本创建v4
  vector<int> v5 = {1, 2, 3, 4, 5};     // 使用初始化列表创建一个向量

  // 赋值操作
  vector<int> v5;
  v5 = v4;           // 使用赋值运算符
  v5.assign(7, 100); // 将v5的内容替换为7个值为100的元素

  // 元素访问
  int firstElement = v5[0];     // 访问第一个元素
  int secondElement = v5.at(1); // 访问第二个元素，如果索引越界会抛出 out_of_range获取第一个和最后一个元素：
  int first = v5.front();       // 获取第一个元素
  int last = v5.back();         // 获取最后一个元素

  // 迭代器
  for (auto it = v5.begin(); it != v5.end(); ++it)
  {
    cout << *it << ' ';
  }

  for (int &value : v5)
  {
    cout << value << endl;
  }

  cout << endl;

  // 容量
  if (!v5.empty())
  { // 检查非空
    cout << "Size of v5: " << v5.size() << endl;
  }
  v2.resize(15);                   // 将v2的大小改变为15个元素
  size_t capacity = v2.capacity(); // 获取v2的容量
  v2.reserve(20);                  // 将v2的容量增加到至少20

  // 修改操作
  v5.push_back(200);          // 在尾部添加元素
  v5.pop_back();              // 移除尾部元素
  v5.insert(v5.begin(), 300); // 在头部插入元素
  v5.erase(v5.begin());       // 移除头部元素
  v5.clear();                 // 清空所有元素

// 向量排序（需要包含 <algorithm> 头文件）：
#include <algorithm>
  // ...
  sort(v5.begin(), v5.end()); // 将v5的元素排序

  // 找到向量中的元素（同样需要 <algorithm>）：
  auto it = find(v5.begin(), v5.end(), 3); // 找到值为3的元素的迭代器

  return 0;
}
```
     
    ！！！
    resize 改变向量的大小（即元素的数量），可能会创建新的元素或销毁现有元素；

    而 reserve 只是确保向量有足够的容量来存储指定数量的元素，避免频繁的内存分配，但不会改变向量的大小。

```cpp

#include <vector>
#include <iostream>

using namespace std;


int main() {
    vector<int> v;

    // 初始时，向量可能有一个小的容量或者没有分配内存
    cout << "Initial capacity: " << v.capacity() << "\n";

    // 增加向量的容量到100，但不添加新元素
    v.reserve(100);
    cout << "Capacity after reserve: " << v.capacity() << "\n"; // 输出: 至少100，取决于实现

    // 实际向量的大小仍然为0，因为没有添加新元素
    cout << "Size after reserve: " << v.size() << "\n"; // 输出: 0

    return 0;
}


```

##### 其他用法 

（1）emplace_back()

***末尾直接构造，比 push_back() 高效***

    emplace_back() 方法用来在 vector 的末尾直接构造一个新元素。它可以接受任意数量和类型的参数，
    并将这些参数传递给元素类型的构造函数。这比先构造一个临时对象再插入到向量中（使用 push_back()）更高效

```CPP

#include <vector>
#include <string>

using namespace std;

int main() 
{
    vector<string> v;

    // 使用 push_back 添加字符串
    v.push_back(string("Hello"));

    // 使用 emplace_back 直接在向量的末尾构造字符串
    v.emplace_back("World"); // 不需要构造临时 string 对象

    return 0;
}

```

（2）emplace()

***指定位置直接构造，比 push_back() 高效***

    emplace() 方法类似于 emplace_back()，但它允许你在 vector 的任意位置直接构造新元素。
    你需要传递一个指向插入位置的迭代器，紧接着是构造新元素所需的参数。

```cpp

#include <vector>

using namespace std;

int main() 
{
    vector<int> v{1, 2, 4, 5};

    // 在第三个元素位置构造一个新元素 3
    v.emplace(v.begin() + 2, 3); // v 现在是 {1, 2, 3, 4, 5}

    return 0;
}
```

（3）swap()

***同类型 vector 交换***
    
    swap() 方法交换两个同类型 vector 的内容。这是个非常高效的操作，通常只涉及指针的交换。

```cpp

#include <vector>
#include <algorithm> // 为了 swap

int main() 
{
    vector<int> v1{1, 2, 3};
    vector<int> v2{4, 5, 6};

    // 交换 v1 和 v2 的内容
    v1.swap(v2); // 或者 swap(v1, v2);

    return 0;
}

```

（4）data()

***返回指向 vector 存储的第一个元素的指针***

    data() 方法返回一个指向 vector 存储的第一个元素的指针
    
    这可以用来 与需要原始数组的 C 函数接口进行交互

```cpp

#include <vector>
#include <cstring> // 为了使用 memcpy

using namespace std;

int main() 
{
    vector<char> v{'H', 'e', 'l', 'l', 'o'};
    char buffer[6];

    // 将 vector 的内容复制到字符数组
    memcpy(buffer, v.data(), v.size());
    buffer[5] = '\0'; // 添加空字符作为字符串的末尾

    return 0;
}

```

（5）assign()

***替换***

    assign() 方法用来 替换 vector 中的所有元素。它可以填充向量具有特定数量的拷贝一个给定值，或者用一个元素范围或初始化列表的内容来替换当前内容。

```cpp

#include <vector>

int main() 
{
    vector<int> v;

    // 用 5 个 2 来填充向量
    v.assign(5, 2); // v 现在是 {2, 2, 2, 2, 2}

    // 用初始化列表的内容替换向量的内容
    v.assign({1, 2, 3}); // v 现在是 {1, 2, 3}

    return 0;
}
```

    ！！！
    emplace 类方法可以避免不必要的对象拷贝，从而提升性能。
    
    swap 在需要交换两个向量的内容时非常快，因为它不进行元素级别的拷贝。
    
    data() 方法提供了一个方便的接口，使得向量可以与期望使用原始数组的 C API 兼容。
    
    最后，assign 方法则是用来批量替换向量中的元素。

#### 2. list

    C++ 标准库中的 list 是一个双向链表容器, 它允许高效地在容器中的任何位置插入和删除元素

    允许在容器的两端快速插入和删除元素， 代价是放弃随机访问功能

##### 常用的 list 成员函数和操作

（1） 创建 list

    list<int> lst; // 创建一个空的 list

    list<int> lst2(5, 10); // 创建一个包含 5 个值为 10 的元素的 list

（2） 基本操作
   
    push_back: 在列表末尾添加元素

    push_front: 在列表头部添加元素

    pop_back: 移除列表末尾元素

    pop_front: 移除列表头部元素

    front: 访问列表头部元素

    back: 访问列表末尾元素

    empty: 检查列表是否为空

    size: 获取列表中的元素数量

    clear: 清空列表

    insert: 在指定位置插入元素

    erase: 删除指定位置的元素

    begin, end: 获取迭代器

    rbegin, rend: 获取逆向迭代器

###### 示例代码 1

```cpp

#include <iostream>
#include <list>

using namespace std;

int main() 
{
    list<int> lst;

    // 在列表末尾添加元素
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    // 在列表头部添加元素
    lst.push_front(0);

    // 访问列表头部和尾部元素
    cout << "Front element: " << lst.front() << endl; // 输出 0
    cout << "Back element: " << lst.back() << endl; // 输出 30

    // 列表大小
    cout << "List size: " << lst.size() << endl; // 输出 4

    // 移除列表头部和尾部元素
    lst.pop_front();
    lst.pop_back();

    // 访问并遍历列表
    for (int value : lst) 
    {
        cout << value << " "; // 输出: 10 20
    }
    cout << endl;

    // 插入元素
    auto it = lst.begin();
    ++it; // 移动到第二个位置
    lst.insert(it, 15); // 在第二个位置插入 15

    // 删除元素
    it = lst.begin();
    ++it; // 移动到第二个位置
    lst.erase(it); // 删除第二个元素

    // 遍历列表
    for (int value : lst) 
    {
        cout << value << " "; // 输出: 10 20
    }
    cout << endl;

    // 清空列表
    lst.clear();
    cout << "List size after clear: " << lst.size() << endl; // 输出 0

    return 0;
}

```

##### 其他操作

    splice: 将一个列表的元素移动到另一个列表中

    remove: 移除所有等于指定值的元素

    remove_if: 按条件移除元素

    unique: 移除连续重复的元素

    sort: 对列表进行排序
    
    merge: 合并两个已排序的列表

    reverse: 反转列表中的元素

###### 示例代码 2

```cpp
#include <iostream>
#include <list>

bool isOdd(int n) 
{
    return n % 2 != 0;
}

using namespace std;

int main() 
{
    list<int> lst1 = {1, 2, 3, 4, 5};
    list<int> lst2 = {10, 20, 30};
    
    // splice: 将 lst2 的内容移动到 lst1 的第二个位置
    auto it = lst1.begin();
    ++it; // 移动到第二个位置
    lst1.splice(it, lst2);

    // lst1 现在包含: 1 10 20 30 2 3 4 5
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 1 10 20 30 2 3 4 5

    // remove: 移除所有等于 2 的元素
    lst1.remove(2);

    // lst1 现在包含: 1 10 20 30 3 4 5
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 1 10 20 30 3 4 5

    // remove_if: 按条件移除元素，移除所有奇数
    lst1.remove_if(isOdd);

    // lst1 现在包含: 10 20 30 4
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 10 20 30 4

    // unique: 移除连续重复的元素
    lst1.push_back(4);
    lst1.unique();

    // lst1 现在包含: 10 20 30 4
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 10 20 30 4

    // sort: 对列表进行排序
    lst1.sort();

    // lst1 现在包含: 4 10 20 30
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 4 10 20 30

    // merge: 合并两个已排序的列表
    list<int> lst3 = {5, 15, 25};
    lst1.merge(lst3);

    // lst1 现在包含: 4 5 10 15 20 25 30
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 4 5 10 15 20 25 30

    // reverse: 反转列表
    lst1.reverse();

    // lst1 现在包含: 30 25 20 15 10 5 4
    for (int value : lst1) 
    {
        cout << value << " ";
    }
    cout << endl; // 输出: 30 25 20 15 10 5 4

    return 0;
}

```

###### 示例代码 3

```cpp

#include <list>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

int main() 
{
    list<int> lst = {1, 2, 3, 4, 5};
    vector<int> vec = {10, 20, 30, 40, 50};

    //text1-----------------------------------------------------------------------
    copy(vec.begin(), vec.end(), front_inserter(lst));
    // 使用 front_inserter 将 vec 的元素复制到 lst 的前面
    // 注意 1st 是 list 不是 vector, 因此可以用 front_inserter
    for (int val : lst) 
    {
        cout << val << " ";
    }
    cout << "\n";
    //输出50 40 30 20 10 1 2 3 4 5 （逆序）


    //text2-----------------------------------------------------------------------
    auto it1 = lst.begin(); // 找到插入点
    copy(vec.begin(), vec.end(), inserter(lst, it1));

    for (int val : lst) 
    {
        cout << val << " ";
    }
    cout << "\n";
    //输出10 20 30 40 50 50 40 30 20 10 1 2 3 4 5 （正序）


    //text3-----------------------------------------------------------------------
    auto it = next(lst.begin(), 5); // 找到插入点
    copy(vec.begin(), vec.end(), inserter(lst, it));
    // 使用 inserter 将 vec 的元素复制到 lst 的中间 


    for (int val : lst) 
    {
        cout << val << " ";
    }
    cout << "\n";
    //输出10 20 30 40 50 10 20 30 40 50 50 40 30 20 10 1 2 3 4 5 （正序）


    return 0;
}
```

#### 3. deque

    C++ 标准库中的 deque （双端队列）是一个序列容器
    允许在容器的两端快速插入和删除元素， 支持随机访问功能

##### 常用的 deque 成员函数和操作

（1）创建 deque

    deque<int> dq; // 创建一个空的 deque

    deque<int> dq2(5, 10); // 创建一个包含 5 个值为 10 的元素的 deque

    deque<int> dq3 = {1, 2, 3, 4, 5}; // 使用初始化列表

（2） 基本操作

    push_back: 在末尾添加元素

    push_front: 在头部添加元素

    pop_back: 移除末尾元素deque

    pop_front: 移除头部元素

    front: 访问头部元素

    back: 访问末尾元素

    empty: 检查是否为空

    size: 获取元素数量

    clear: 清空容器

    insert: 在指定位置插入元素

    erase: 删除指定位置的元素

    begin, end: 获取迭代器

    rbegin, rend: 获取逆向迭代器

    operator[]: 随机访问元素

###### 示例代码 1

```cpp
#include <iostream>
#include <deque>

using namespace std;

int main() 
{
    deque<int> dq;

    // 在末尾添加元素
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);

    // 在头部添加元素
    dq.push_front(0);

    // 访问头部和尾部元素
    cout << "Front element: " << dq.front() << endl; // 输出 0
    cout << "Back element: " << dq.back() << endl; // 输出 30

    // 容器大小
    cout << "Deque size: " << dq.size() << endl; // 输出 4

    // 移除头部和尾部元素
    dq.pop_front();
    dq.pop_back();

    // 访问并遍历容器
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 10 20
    }
    cout << endl;

    // 插入元素
    auto it = dq.begin();
    ++it; // 移动到第二个位置
    dq.insert(it, 15); // 在第二个位置插入 15

    // 删除元素
    it = dq.begin();
    ++it; // 移动到第二个位置
    dq.erase(it); // 删除第二个元素

    // 遍历容器
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 10 20
    }
    cout << endl;

    // 访问元素
    dq.push_back(25);
    cout << "Element at index 0: " << dq[0] << endl; // 输出 10
    cout << "Element at index 1: " << dq[1] << endl; // 输出 20
    cout << "Element at index 2: " << dq[2] << endl; // 输出 25

    // 清空容器
    dq.clear();
    cout << "Deque size after clear: " << dq.size() << endl; // 输出 0

    return 0;
}
```

(3) 其他操作

    resize: 改变容器大小

    shrink_to_fit: 减少容量以适应大小

    assign: 重新填充容器

    swap: 交换两个容器的内容

    emplace, emplace_back, emplace_front: 原地构造元素

###### 示例代码 2

```cpp

#include <iostream>
#include <deque>

using namespace std;

int main() 
{
    deque<int> dq = {1, 2, 3, 4, 5};

    // resize: 改变容器大小
    dq.resize(3);
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 1 2 3
    }
    cout << endl;

    dq.resize(5, 10);
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 1 2 3 10 10
    }
    cout << endl;

    // shrink_to_fit: 减少容量
    dq.shrink_to_fit();

    // assign: 重新填充容器
    dq.assign(4, 7);
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 7 7 7 7
    }
    cout << endl;

    // swap: 交换两个容器的内容
    deque<int> dq2 = {100, 200};
    dq.swap(dq2);
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 100 200
    }
    cout << endl;

    for (int value : dq2) 
    {
        cout << value << " "; // 输出: 7 7 7 7
    }
    cout << endl;

    // emplace, emplace_back, emplace_front: 原地构造元素
    dq.emplace_back(300); // 在末尾原地构造 300
    dq.emplace_front(50); // 在头部原地构造 50
    dq.emplace(dq.begin() + 1, 75); // 在第二个位置原地构造 75

    // 现在 dq 包含: 50 75 100 200 300
    for (int value : dq) 
    {
        cout << value << " "; // 输出: 50 75 100 200 300
    }
    cout << endl;

    return 0;
}
```

---

### 二、容器适配器

#### 4. queue

    C++ 标准库中的 queue 是一种容器适配器, 它提供了一个先进先出(FIFO)的数据结构

    queue 一般使用 deque 或 list 作为底层容器, 但也可以使用其他支持双端操作的容器

##### 常用的 queue 成员函数和操作

（1）创建 queue
    
    a. 默认情况下, queue 使用 deque 作为底层容器: queue<int> q; 
    
    b. 也可以显式指定底层容器: queue<int, list<int>> q2; // 使用 list 作为底层容器

(2) 基本操作

    push: 向队列尾部添加元素

    pop: 移除队列头部元素

    front: 访问队列头部元素

    back: 访问队列尾部元素

    empty: 检查队列是否为空

    size: 获取队列中的元素数量

###### 示例代码 1

```cpp
//使用默认底层容器

#include <iostream>
#include <queue>

using namespace std;

int main() 
{
    queue<int> q;

    // 向队列添加元素
    q.push(10);
    q.push(20);
    q.push(30);

    // 访问队列头部元素
    cout << "Front element: " << q.front() << endl; // 输出 10

    // 访问队列尾部元素
    cout << "Back element: " << q.back() << endl; // 输出 30

    // 队列大小
    cout << "Queue size: " << q.size() << endl; // 输出 3

    // 移除队列头部元素
    q.pop();
    cout << "Front element after pop: " << q.front() << endl; // 输出 20

    // 检查队列是否为空
    if (q.empty()) 
    {
        cout << "Queue is empty" << endl;
    } else 
    {
        cout << "Queue is not empty" << endl; // 输出 Queue is not empty
    }

    return 0;
}
```

###### 示例代码 2

```cpp

//使用自定义底层容器

#include <iostream>
#include <queue>
#include <list>

using namespace std;

int main() 
{
    queue<int, list<int>> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.front() << endl; // 输出 10
    cout << "Back element: " << q.back() << endl; // 输出 30

    return 0;
}

```

###### 示例代码 3 

```cpp

//遍历队列
//queue 不提供直接的迭代器访问，因此遍历队列需要使用 pop 操作来逐个访问元素。注意, pop 操作会移除元素

#include <iostream>
#include <queue>

using namespace std;

int main() 
{
    queue<int> q;

    // 向队列添加元素
    q.push(10);
    q.push(20);
    q.push(30);

    // 遍历队列
    while (!q.empty()) 
    {
        cout << q.front() << " "; // 输出元素
        q.pop(); // 移除元素
    }
    cout << endl; // 输出: 10 20 30

    return 0;
}
```

(3) 使用优先级队列(priority_queue)
    
    priority_queue 是一个容器适配器，提供了优先队列的功能。

    优先队列是一种数据结构，其中每个元素都有一个优先级，元素根据优先级顺序进行出队操作。
    
    默认情况下，priority_queue 是一个最大堆（即优先级最高的元素先出队），但你也可以自定义比较函数来实现最小堆。

    所有 priority_queue 的使用都需要包含 <queue> 头文件

##### 常用的 priority_queue 成员函数和操作

    1. 创建 priority_queue

        priority_queue<int> pq1; // 默认使用 vector 作为底层容器，最大堆

        priority_queue<int, vector<int>, greater<int>> pq2; // 最小堆

    2. 基本操作

        push: 向优先队列添加元素

        pop: 移除优先队列的顶部元素

        top: 访问优先队列的顶部元素

        empty: 检查优先队列是否为空

        size: 获取优先队列中的元素数量


###### 示例代码 4

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() 
{
    priority_queue<int> pq; // 默认最大优先级队列

    // 添加元素
    pq.push(30);
    pq.push(10);
    pq.push(20);

    // 访问并移除元素
    while (!pq.empty()) 
    {
        cout << pq.top() << " "; // 输出最大元素
        pq.pop(); // 移除最大元素
    }
    cout << endl; // 输出: 30 20 10

    return 0;
}

```

```cpp

// 自定义比较器以创建最小优先级队列：

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for greater<int>

using namespace std;

int main() 
{
    // 使用 greater<int> 创建最小优先级队列
    priority_queue<int, vector<int>, greater<int>> pq;

    // 添加元素
    pq.push(30);
    pq.push(10);
    pq.push(20);

    // 访问并移除元素
    while (!pq.empty()) {
        cout << pq.top() << " "; // 输出最小元素
        pq.pop(); // 移除最小元素
    }
    cout << endl; // 输出: 10 20 30

    return 0;
}
```

###### 示例代码 5

```cpp
// 使用自定义数据类型和比较器
// 可以使用自定义数据类型和比较器。例如，假设有一个任务调度系统，其中任务有不同的优先级。

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Task 
{
    int priority;
    string description;

    // 自定义比较器，用于最大堆
    bool operator<(const Task& other) const 
    {
        return priority < other.priority;
    }
};

int main() 
{
    priority_queue<Task> task_queue;

    // 向任务队列添加任务
    task_queue.push({1, "Low priority task"});
    task_queue.push({3, "High priority task"});
    task_queue.push({2, "Medium priority task"});

    // 访问并移除优先级最高的任务
    while (!task_queue.empty()) 
    {
        Task top_task = task_queue.top();
        cout << "Task: " << top_task.description << " with priority " << top_task.priority << endl;
        task_queue.pop();
    }

    return 0;
}
```

###### 使用 priority_queue 解决实际问题

```cpp

// 合并 K 个排序链表
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct compare 
{
    bool operator()(const ListNode* l1, const ListNode* l2) 
    {
        return l1->val > l2->val; // 最小堆重载大于号
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) 
{
    priority_queue<ListNode*, vector<ListNode*>, compare> pq;

    // 初始化优先队列
    for (ListNode* list : lists) 
    {
        if (list) pq.push(list);
    }

    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (!pq.empty()) 
    {
        ListNode* top = pq.top(); //pq.top() 获取优先队列中值最小的节点（也就是当前最小的头节点）
        pq.pop();
        curr->next = top;
        curr = curr->next;
        if (top->next) pq.push(top->next); //检查当前节点 top 的后继节点是否存在(针对待合并的一条链表)
    }

    return dummy.next;
}

int main() 
{
    // 创建示例链表
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    vector<ListNode*> lists = {l1, l2, l3};

    ListNode* merged_list = mergeKLists(lists);

    // 打印合并后的链表
    ListNode* curr = merged_list;
    while (curr) 
    {
        cout << curr->val << " ";
        curr = curr->next;
    }

    // 释放内存
    while (merged_list) 
    {
        ListNode* temp = merged_list;
        merged_list = merged_list->next;
        delete temp;
    }

    return 0;
}

```

#### 5. stack

    C++ 标准库中的 stack 是一个容器适配器，提供了以 LIFO (后进先出)顺序存储元素的功能
    它通常是基于 deque 或 vector 实现的

##### 常用的 stack 成员函数和操作

(1) 创建 stack

    stack<int> stack1; // 使用默认的底层容器（通常是 deque）

    stack<int, vector<int>> stack2; // 使用 vector 作为底层容器

(2) 基本操作

    push: 向栈顶添加元素

    pop: 移除栈顶元素

    top: 访问栈顶元素

    empty: 检查栈是否为空

    size: 获取栈中的元素数量

###### 示例代码 1

```cpp

#include <iostream>
#include <stack>

using namespace std;

int main() 
{
    // 创建一个空的栈
    stack<int> stack;

    // 向栈顶添加元素
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 访问栈顶元素
    cout << "Top element: " << stack.top() << endl; // 输出 30

    // 栈的大小
    cout << "Stack size: " << stack.size() << endl; // 输出 3

    // 移除栈顶元素
    stack.pop();

    // 再次访问栈顶元素
    cout << "Top element after pop: " << stack.top() << endl; // 输出 20

    // 检查栈是否为空
    if (stack.empty()) 
    {
        cout << "Stack is empty" << endl;
    } else {
        cout << "Stack is not empty" << endl; // 输出 Stack is not empty
    }

    // 再次移除所有元素
    stack.pop();
    stack.pop();

    // 最后检查栈是否为空
    if (stack.empty()) 
    {
        cout << "Stack is empty" << endl; // 输出 Stack is empty
    }

    return 0;
}

```

###### 示例代码 2

```cpp

// 使用自定义底层容器
// 标准库的 stack 允许使用自定义的底层容器，只要它支持操作：empty，size， back，push_back，pop_back
// 例如，使用 vector 作为底层容器：

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() 
{
    // 使用 vector 作为底层容器
    stack<int, vector<int>> stack;

    // 向栈顶添加元素
    stack.push(100);
    stack.push(200);
    stack.push(300);

    // 访问栈顶元素
    cout << "Top element: " << stack.top() << endl; // 输出 300

    // 移除栈顶元素
    stack.pop();

    // 再次访问栈顶元素
    cout << "Top element after pop: " << stack.top() << endl; // 输出 200

    return 0;
}
```

##### 常用应用示例

###### 1. 括号匹配检查器

```cpp

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValidParentheses(const string& s) 
{
    stack<char> stack;
    for(char c : s)
    {
        if(c == '(' || c == '{' || c == '[') stack.push(c);
        else
        {
            if(stack.empty()) return false;
            if((c == ')' && stack.top() != '(') || (c == ']' && stack.top() != '[') || (c == '}' && stack.top() != '{'))
                return false;
            stack.pop();
        }
    }
    return stack.empty();
}

int main() 
{
    string s = "{[()]}";
    if (isValidParentheses(s)) 
    {
        cout << "Valid parentheses!" << endl;
    } else 
    {
        cout << "Invalid parentheses!" << endl;
    }
    return 0;
}
```

###### 2. 反转字符串

```cpp

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string reverseString(const string& s) 
{
    stack<char> stack;
    for(char c : s) stack.push(c);
    string res;
    while(!stack.empty())
    {
        res += stack.top();
        stack.pop();
    }
    return res;
}

int main() 
{
    string s = "hello";
    cout << "Original string: " << s << endl;
    cout << "Reversed string: " << reverseString(s) << endl;
    return 0;
}
```

---

### 三、关联容器

#### 6. map

    <map> 是 C++ 标准库中的一个头文件，提供了 map 和 multimap 容器, 这些容器用于存储键值对，并按键自动排序

##### (1) map 基本使用

map 是一个存储有序键值对的容器，每个键都是唯一的

```cpp

#include <iostream>
#include <map>

using namespace std;

int main() 
{
    // 创建一个空的 map
    map<int, string> m;

    // 插入元素
    m.insert({1, "one"});
    m.insert({2, "two"});
    m.insert({3, "three"});

    // 使用下标运算符插入/修改元素
    m[4] = "four";
    m[2] = "TWO";  // 修改键为 2 的值

    // 输出元素
    cout << "Map elements:" << endl;
    for (const auto &pair : m) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 查找元素
    auto it = m.find(3);
    if (it != m.end()) 
    {
        cout << "Element with key 3 found: " << it->second << endl;
    } else {
        cout << "Element with key 3 not found." << endl;
    }

    // 删除元素
    m.erase(2);

    // 输出元素
    cout << "Map elements after erasing key 2:" << endl;
    for (const auto &pair : m) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
```

##### (2) multimap 基本使用

multimap 类似于 map, 但允许存储重复的键

!!!查找重复的键：用 equal_range；for (auto it = range.first; it != range.second; ++it) 

```cpp

#include <iostream>
#include <map>

using namespace std;

int main() 
{
    // 创建一个空的 multimap
    multimap<int, string> mm;

    // 插入元素
    mm.insert({1, "one"});
    mm.insert({2, "two"});
    mm.insert({3, "three"});
    mm.insert({2, "TWO"}); // 重复键

    // 输出元素
    cout << "Multimap elements:" << endl;
    for (const auto &pair : mm) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // !!!!查找元素
    auto range = mm.equal_range(2);
    cout << "Elements with key 2:" << endl;
    for (auto it = range.first; it != range.second; ++it) 
    {
        cout << it->first << ": " << it->second << endl;
    }

    // 删除某个键的所有元素
    mm.erase(2);

    // 输出元素
    cout << "Multimap elements after erasing key 2:" << endl;
    for (const auto &pair : mm) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}

```

##### (3) map 其他重要功能

以下示例展示了 map 的一些其他重要功能，
包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range 

```cpp

#include <iostream>
#include <map>

using namespace std;

int main() 
{
    map<int, string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

    // 大小和是否为空
    cout << "Size of map: " << m.size() << endl;
    cout << "Is map empty? " << boolalpha << m.empty() << endl;

    // 清除所有元素
    m.clear();
    cout << "Size of map after clear: " << m.size() << endl;

    // 重新插入元素
    m[2] = "two";
    m[4] = "four";
    m[6] = "six";

    // 计数某个键（对于 map 来说，计数结果要么是 0 要么是 1）
    cout << "Count of key 4: " << m.count(4) << endl;
    cout << "Count of key 5: " << m.count(5) << endl;

    // lower_bound 和 upper_bound
    map<int, string>::iterator lb = m.lower_bound(4);
    map<int, string>::iterator ub = m.upper_bound(4);
    if (lb != m.end()) 
    {
        cout << "Lower bound of key 4: " << lb->first << ": " << lb->second << endl;
    }
    if (ub != m.end()) 
    {
        cout << "Upper bound of key 4: " << ub->first << ": " << ub->second << endl;
    }

    // equal_range
    auto range = m.equal_range(4);
    if (range.first != m.end()) 
    {
        cout << "Equal range first of key 4: " << range.first->first << ": " << range.first->second << endl;
    }
    if (range.second != m.end()) 
    {
        cout << "Equal range second of key 4: " << range.second->first << ": " << range.second->second << endl;
    }

    return 0;
}

```

##### (4) multimap 其他重要功能

以下示例展示了 multimap 的一些其他重要功能，

包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range

```cpp

#include <iostream>
#include <map>

using namespace std;

int main() 
{
    multimap<int, string> mm = {{1, "one"}, {2, "two"}, {3, "three"}, {2, "TWO"}};

    // 大小和是否为空
    cout << "Size of multimap: " << mm.size() << endl;
    cout << "Is multimap empty? " << boolalpha << mm.empty() << endl;

    // 清除所有元素
    mm.clear();
    cout << "Size of multimap after clear: " << mm.size() << endl;

    // 重新插入元素
    mm.insert({2, "two"});
    mm.insert({4, "four"});
    mm.insert({6, "six"});
    mm.insert({4, "FOUR"});

    // 计数某个键（对于 multimap，计数可以大于 1）
    cout << "Count of key 4: " << mm.count(4) << endl;
    cout << "Count of key 5: " << mm.count(5) << endl;

    // lower_bound 和 upper_bound
    multimap<int, string>::iterator lb = mm.lower_bound(4);
    multimap<int, string>::iterator ub = mm.upper_bound(4);
    if (lb != mm.end()) 
    {
        cout << "Lower bound of key 4: " << lb->first << ": " << lb->second << endl;
    }
    if (ub != mm.end()) 
    {
        cout << "Upper bound of key 4: " << ub->first << ": " << ub->second << endl;
    }

    // equal_range
    auto range = mm.equal_range(4);
    if (range.first != mm.end()) 
    {
        cout << "Equal range first of key 4: " << range.first->first << ": " << range.first->second << endl;
    }
    if (range.second != mm.end()) 
    {
        cout << "Equal range second of key 4: " << range.second->first << ": " << range.second->second << endl;
    }

    return 0;
}
```

#### 7. set

    <set> 是 C++ 标准库中的一个头文件，提供了 set 和 multiset 容器
    这些容器用于存储有序的唯一元素 (对于 set) 和有序的非唯一元素 (对于 multiset) 

##### (1) set 基本使用

    set 是一个存储唯一元素的有序集合

```cpp

#include <iostream>
#include <set>

using namespace std;

int main() 
{
    // 创建一个空的 set
    set<int> s;

    // 插入元素
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(2); // 重复插入的元素不会被添加

    // 输出元素
    cout << "Set elements: ";
    for (const int &elem : s) 
    {
        cout << elem << " ";
    }
    cout << endl;

    // 查找元素
    auto it = s.find(2);
    if (it != s.end()) 
    {
        cout << "Element 2 found." << endl;
    } else 
    {
        cout << "Element 2 not found." << endl;
    }

    // 删除元素
    s.erase(2);

    // 输出元素
    cout << "Set elements after erasing 2: ";
    for (const int &elem : s) 
    {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
```

##### (2) multiset 基本使用

    multiset 类似于 set, 但允许存储重复元素


```cpp

#include <iostream>
#include <set>

using namespace std;

int main() 
{
    // 创建一个空的 multiset
    multiset<int> ms;

    // 插入元素
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(2); // 重复插入的元素会被添加

    // 输出元素
    cout << "Multiset elements: ";
    for (const int &elem : ms) 
    {
        cout << elem << " ";
    }
    cout << endl;

    // 查找元素
    auto it = ms.find(2);
    if (it != ms.end()) 
    {
        cout << "Element 2 found." << endl;
    } else 
    {
        cout << "Element 2 not found." << endl;
    }

    // 删除某个元素
    ms.erase(ms.find(2)); // 删除一个 2

    // 输出元素
    cout << "Multiset elements after erasing one 2: ";
    for (const int &elem : ms) 
    {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
```

##### (3) set 其他重要功能

以下示例展示了 set 的一些其他重要功能，

包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range


```cpp

#include <iostream>
#include <set>

using namespace std;

int main() 
{
    set<int> s = {1, 2, 3, 4, 5};

    // 大小和是否为空
    cout << "Size of set: " << s.size() << endl;
    cout << "Is set empty? " << boolalpha << s.empty() << endl;

    // 清除所有元素
    s.clear();
    cout << "Size of set after clear: " << s.size() << endl;

    // 重新插入元素
    s.insert({2, 4, 6, 8, 10});

    // 计数某个元素（对于 set 来说，计数结果要么是 0 要么是 1）
    cout << "Count of element 4: " << s.count(4) << endl;
    cout << "Count of element 5: " << s.count(5) << endl;

    // lower_bound 和 upper_bound
    set<int>::iterator lb = s.lower_bound(4);
    set<int>::iterator ub = s.upper_bound(4);
    if (lb != s.end()) 
    {
        cout << "Lower bound of 4: " << *lb << endl;
    }
    if (ub != s.end()) 
    {
        cout << "Upper bound of 4: " << *ub << endl;
    }

    // equal_range
    auto range = s.equal_range(4);
    if (range.first != s.end()) 
    {
        cout << "Equal range first of 4: " << *range.first << endl;
    }
    if (range.second != s.end()) 
    {
        cout << "Equal range second of 4: " << *range.second << endl;
    }

    return 0;
}
```

##### (4) multiset 其他重要功能

以下示例展示了 multiset 的一些其他重要功能，

包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range。


```cpp
#include <iostream>
#include <set>

using namespace std;

int main() 
{
    multiset<int> ms = {1, 2, 3, 4, 5, 5, 5};

    // 大小和是否为空
    cout << "Size of multiset: " << ms.size() << endl;
    cout << "Is multiset empty? " << boolalpha << ms.empty() << endl;

    // 清除所有元素
    ms.clear();
    cout << "Size of multiset after clear: " << ms.size() << endl;

    // 重新插入元素
    ms.insert({2, 4, 6, 8, 10, 10, 10});

    // 计数某个元素（对于 multiset，计数可以大于 1）
    cout << "Count of element 4: " << ms.count(4) << endl;
    cout << "Count of element 10: " << ms.count(10) << endl;

    // lower_bound 和 upper_bound
    multiset<int>::iterator lb = ms.lower_bound(4);
    multiset<int>::iterator ub = ms.upper_bound(4);
    if (lb != ms.end()) 
    {
        cout << "Lower bound of 4: " << *lb << endl;
    }
    if (ub != ms.end()) 
    {
        cout << "Upper bound of 4: " << *ub << endl;
    }

    // equal_range
    auto range = ms.equal_range(10);
    if (range.first != ms.end()) {

        cout << "Equal range first of 10: " << *range.first << endl;
    }
    if (range.second != ms.end()) 
    {
        cout << "Equal range second of 10: " << *range.second << endl;
    }

    return 0;
}
```

---

### 四、算法

#### 8. algorithm

##### 常用算法的简要列表

###### (1) 非修改序列操作

    all_of, any_of, none_of: 检查序列中的元素是否满足特定条件

    for_each: 对序列中每个元素执行函数
    
    count, count_if: 计算满足特定条件的元素数量

    mismatch: 返回第一个不匹配的元素对

    find, find_if, find_if_not: 查找满足条件的元素

###### (2) 修改序列操作

    copy, copy_if, copy_n: 复制元素到另一个位置

    move: 移动元素到另一个位置

    transform: 对序列中的元素应用一个函数，并存放结果

    swap, iter_swap: 交换两个元素

    fill, fill_n: 用特定值填充序列

    generate, generate_n: 用生成器函数填充序列

    replace, replace_if: 替换序列中满足条件的元素

###### (3) 排序和相关操作

    sort: 对序列进行排序

    stable_sort: 对序列进行稳定排序

    partial_sort: 部分排序序列

    nth_element: 重新排列序列，以使得第 n 个元素处于它最终排序完成后的位置

###### (4) 二分搜索操作（在有序序列上）

    lower_bound, upper_bound: 查找某个值的边界

    binary_search: 检查某个值是否存在

    equal_range: 同时获取lower_bound和upper_bound

###### (5) 集合操作（在有序序列上）

    merge: 合并两个有序序列

    inplace_merge: 在原地合并两个有序序列

    includes: 检查一个有序序列是否包含另一个序列

    set_union, set_intersection, set_difference, set_symmetric_difference: 对两个集合执行集合操作

###### (6) 最小/最大操作

    max, min: 返回两个值中的最大值或最小值

    max_element, min_element: 查找序列中的最大或最小元素

    clamp: 将值限制在指定的范围内（C++17 中引入）

###### (7) 比较操作

    equal: 检查两个序列是否相等
    lexicographical_compare: 字典顺序比较两个序列

###### (8) 排列操作

    next_permutation, prev_permutation: 生成序列的下一个或上一个排列

###### (9) 堆操作

    make_heap, push_heap, pop_heap, sort_heap: 创建和管理堆

##### 常用算法的用法


###### (1) 非修改序列操作

***all_of, any_of, none_of ***

```cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//不改序列
int main()
{
    vector<int> v = {2, 4, 6, 8, 10};
    bool allEven = all_of(v.begin(), v.end(), [](int i) { 
        return i % 2 == 0; 
        });
    cout << "All are even: " << allEven << '\n';
    bool anyEven = any_of(v.begin(), v.end(), [](int i) { 
        return i % 2 == 0; 
        });
    cout << "Any is even: " << anyEven << '\n';
    bool noneEven = none_of(v.begin(), v.end(), [](int i) { 
        return i % 2 == 0; 
        });
    cout << "None are even: " << noneEven << '\n';
}
```

---

***for_each***

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    for_each(v.begin(), v.end(), [](int& n) { 
        n *= 2; 
        }); // 对每个元素执行函数，不改变元素
    for (int n : v) cout << n << ' ';
    cout << '\n';
}
```

---

***count & count_if***

    统计在给定范围内等于某个值的元素的数量
    它可以用于任何容器，如 vector, list, array, string 等

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//不改序列
int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 2};
    int count2 = count(v.begin(), v.end(), 2); // 计算值为2的元素数量
    cout << "Count of 2: " << count2 << '\n';
    int countEven = count_if(v.begin(), v.end(), [](int n) { 
        return n % 2 == 0;
        });
    // 计算偶数的数量
    cout << "Count of even numbers: " << countEven << '\n';
}
```

---

***mismatch***

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//不改序列
int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 0, 4, 5};

    auto mismatch_pair = mismatch(v1.begin(), v1.end(), v2.begin());

    if (mismatch_pair.first != v1.end())
    {
        //输出不匹配的元素
        cout << "First mismatch: " << *mismatch_pair.first << " and " << *mismatch_pair.second << '\n'; //输出First mismatch: 3 and 0

        //输出不匹配的元素位置
        cout << mismatch_pair.first - v1.begin() << " " << mismatch_pair.second - v2.begin();
    }
    else
    {
        cout << "No mismatch\n";
    }
    
}
```

---

***find, find_if, find_if_not***

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//不改序列
int main()
{
    vector<int> v = {1, 2, 3, 4, 5};

    auto it = find(v.begin(), v.end(), 3);
    if (it != v.end()) 
        cout << "Found 3 at position " << (it - v.begin()) << '\n';
    //输出Found 3 at position 2

    it = find_if(v.begin(), v.end(), [](int n) { 
        return n % 2 == 0; 
        });
    if (it != v.end()) 
        cout << "Found even number: " << *it << '\n';
    //输出Found even number: 2

    it = find_if_not(v.begin(), v.end(), [](int n) { 
        return n % 2 == 0; 
        });
    if (it != v.end()) cout << "Found odd number: " << *it << '\n';
    //输出Found odd number: 1
}

```

---

***unique 和 erase 结合使用***

unique 函数模板用于重新排列容器中的元素，使得每个元素只出现一次,

它仅移除相邻重复元素，留下每组相邻重复元素中的第一个元素

为了从容器中彻底移除这些重复的元素，需要与容器的 erase 方法结合使用

这种结合被称为“擦除-删除”惯用法

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 1, 1};

    auto last = unique(vec.begin(), vec.end());
    // unique 仅将连续的重复元素中的多余部分移动到向量的末尾

    vec.erase(last, vec.end());
    // 使用 erase 移除向量末尾的所有重复元素

    //可以合起来写 vec.erase(unique(vec.begin(), vec.end()), vec.end())

    for (int num : vec) cout << num << " ";
    //输出结果为：1 2 3 4 5 1
    cout << "\n";

    return 0;
}
```

***注意到最后的两个 1 没有被视为重复，因为 unique 只处理相邻的重复元素***

---

***remove() 和 remove_if()***

remove 从序列中移除所有等于指定值的元素

它并不真正从容器中删除元素，而是将不应被移除的元素移到序列的开始位置，因为 remove()是一个STL函数不是STL方法

然后返回一个指向"新序列"末尾的迭代器，与 erase 方法结合使用时,它可以实现真正的元素移除

remove_if 类似于 remove，但它允许指定一个谓词(predicate)函数来决定哪些元素应该被移除

```cpp
//使用 remove

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 2, 2, 3};
    auto last = remove(vec.begin(), vec.end(), 2); // 移除所有等于2的元素
    vec.erase(last, vec.end());
    //可以合起来写vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
    for (int num : vec) 
        cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";

    vector<int> vec = {1, 2, 3, 4, 5, 2, 2, 3};
    //vec.remove(2); //错误， vector没有 remove 成员函数（只有 list 有）

    list<int> l = {1, 2, 3, 4, 5, 2, 2, 3};
    auto last = remove(l.begin(), l.end(), 2); // 移除所有等于2的元素
    l.erase(last, l.end());
    //可以合起来写l.erase(remove(l.begin(), l.end(), value), l.end());
    for (int num : l) 
        cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";

    l = {1, 2, 3, 4, 5, 2, 2, 3};
    l.remove(2);
    for (int num : l) cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";
    return 0;
}
```

---

***remove_if***

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    auto last = remove_if(vec.begin(), vec.end(), [](int x) { 
        return x % 2 == 0; 
        });//移除所有偶数元素
    vec.erase(last, vec.end());
    //可以合起来写vec.erase(remove_if(vec.begin(), vec.end(), predicate), vec.end())
    for (int num : vec) cout << num << " ";
    //输出结果为：1 3 5 7
    cout << "\n";

    return 0;
}
```

---

###### (2) 修改序列操作

***copy_n***

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> dest = {1, 3, 4, 6, 2, 4};
    copy_n(v.begin(), 3, dest.begin());
    for (int n : dest) cout << n << ' ';
    //输出1 2 3 6 2 4
    copy_n(v.begin(), 3, back_inserter(dest));
    //三个参数
    for (int n : dest) cout << n << ' ';
    //输出1 2 3 6 2 4 1 2 3
    return 0;
}
```

---

***copy_if***

从 C++11 开始,copy_if 允许从一个容器复制满足特定条件的元素到另一个容器

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    vector<int> src = {1, 2, 3, 4, 5, 6};
    vector<int> dest;
    copy_if(src.begin(), src.end(), back_inserter(dest), [](int x){ 
        return x % 2 == 0; 
        });// 四个参数, 复制偶数

    for (int val : dest) 
        cout << val << " ";
    cout << endl;
    // 输出: 2 4 6
    copy_if(src.begin(), src.end(), inserter(dest, dest.begin()),[](int x){ 
        return x % 2 == 0; 
        });
    for (int val : dest) 
        cout << val << " ";
    cout << endl;
    // 输出: 2 4 6 2 4 6

    //错误写法，vector不支持前端插入
    // copy_if(src.begin(), src.end(), front_inserter(dest), [](int x){ 
    //     return x % 2 == 1;
    //     });
    // for(int val : dest) cout << val << " ";
    // cout << endl;
    return 0;
}
```

***不同容器前端插入的不同：list，deque 和 vector***

    list 或 deque ：这些容器支持高效的前端插入操作 ———> front_inserter

    vector ———> inserter(v, v.begin())

---

***move***

移动元素到另一个位置

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main()
{
    vector<string> src = {"one", "two", "three"};
    vector<string> dest(3);
    move(src.begin(), src.end(), dest.begin());
    for (const auto& s : dest) 
        cout << s << ' ';
    cout << endl;
    for (const auto& s : src) 
        cout << s << ' '; //移动算法
    cout << endl;
    return 0;
}
```

---

***transform***

transform 对容器中的每个元素应用给定的函数，并将结果存储在另一个容器中

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dest(src.size());
    transform(src.begin(), src.end(), dest.begin(),[](int x){ 
        return pow(x, 2); 
    }); 
    //transform 对容器中的每个元素应用给定的函数，并将结果存储在另一个容器中
    for (int val : dest) 
        cout << val << " ";
    cout << endl;
    //输出: 1 4 9 16 25
    for (int val : src) 
        cout << val << " "; //复制算法
    cout << endl;

    string s;
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), [](char ch){ 
        return tolower(ch);
        });
    //将原字符串转换为小写
    cout << s;
    return 0;
}

```

---

***swap & iter_swap***

```cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int a = 5, b = 10;
    swap(a, b); // 交换两个变量的值
    cout << "a: " << a << ", b: " << b << '\n';
    vector<int> v = {1, 2, 3, 4};
    iter_swap(v.begin(), v.begin() + 2); // 使用迭代器交换元素
    for (int n : v) cout << n << ' ';
    //输出 3 2 1 4
    cout << '\n';
}

```

---

***fill & fill_n***

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v(5); // 向量要有初始长度
    fill(v.begin(), v.end(), 1); // 将1填充到整个向量中
    for (int n : v) cout << n << ' ';
    cout << '\n';
    fill_n(v.begin(), 3, 2); // 只填充前3个元素为2
    for (int n : v) cout << n << ' ';
    cout << '\n';
}

```

---

***generate & generate_n***

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v(5);
    int current = 1;
    generate(v.begin(), v.end(), [&current]() { 
        return current *= 2; 
        });
    /*
    [外部变量](参数列表){}
    用生成器函数填充，每次值翻倍
    &current : 捕获变量 current
    */
    for (int n : v) 
        cout << n << ' ';
    //输出 2 4 8 16 32 
    cout << '\n';
}
```

---

***replace & replace_if***

```cpp

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    replace(v.begin(), v.end(), 3, 8); // 将3替换为8, 就地算法
    for (int n : v) 
        cout << n << ' ';
    //输出1 2 8 4 5
    cout << '\n';
    replace_if(v.begin(), v.end(), [](int n) { 
        return n % 2 == 0; 
        }, 10); // 将偶数替换为10
    for (int n : v) cout << n << ' '; //输出1 10 10 10 5
    cout << '\n';
}

```
---

###### (3) 排序和相关操作

***sort***

```cpp

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> vec = {4, 2, 5, 1, 3};
    sort(vec.begin(), vec.end());
    for (int i : vec) 
        cout << i << ' ';
    //输出 1 2 3 4 5
    return 0;
}
```

---

***stable_sort***

对序列进行稳定排序

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<pair<int, char>> v = {{2, 'A'}, {1, 'B'}, {2, 'C'}, {1, 'D'}};
    // 使用自定义结构以展示稳定性
    stable_sort(v.begin(), v.end());
    //具有相等键值的元素在排序后将保持它们原始的顺序

    for (const auto &p : v) cout << p.second << ' ';
    //输出B D A C 
    return 0;
}
```

***注意 vector<pair<int, char>> 和 map<int, char> 的区别***

    a. vector<pair<int, char>>:

        vector 是一个动态数组，可以存储任意类型的元素，包括 pair<int, char>

        在这种用法中，每个 pair 存储一个整数和一个字符，类似于键值对，但没有任何内建的键到值的映射机制

        适用场景:
        
        1. 当需要维护元素的插入顺序时
        2. 当可能有重复的键值时
        3. 当需要频繁地按序访问元素，而不是根据键查找时(例如：存储节点值等于节点索引值图结构我们可以选择 vector<vector<pair<int, int>>>)

    b. map<int, char>

        map 是一个基于红黑树实现的排序关联容器, 它存储的是键值对, 其中每个键唯一, 并且自动按键排序

        适用场景:
        1. 当需要基于键快速查找、更新或删除元素时(例如：存储节点值不等于节点索引值的图结构我们可以选择 map<int, vector<pair<int, int>>>)
        2. 当每个键必须是唯一的时
        3. 当你需要按键排序的键值对集合时


        !!比较和选择
        如果需要保留元素的插入顺序，或者允许键重复：vector<pair<int, char>>

        如果需要快速基于键的查找, 插入和删除，同时键是唯一且自动排序的： map<int, char> 

---

***partial_sort***

部分排序序列,使前n个元素为已排序的最小元素

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {5, 2, 3, 4, 1};

    partial_sort(v.begin(), v.begin() + 3, v.end());
    /*
      第一个参数 v.begin() 指定要排序的范围的起始迭代器
      第二个参数 v.begin() + 3 指定范围内要排序的最后一个元素的下一个位置也就是说，这个位置之前的元素将被排序
      第三个参数 v.end() 指定要排序的范围的结束迭代器
    */

    for (int n : v) cout << n << ' ';
    //输出1 2 3 5 4 
    return 0;
}
```

***partial_sort 和 inplace_merge 比较记忆***

    partial_sort 适用于需要找到 "前 k 个 "最小元素的场景

    inplace_merge 用于合并操作，特别是在归并排序中

---

***nth_element***

重新排列序列,以使得第n个元素处于其最终排序完成后的位置

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {5, 2, 3, 4, 1, 6};
    nth_element(v.begin(), v.begin() + 3, v.end());
    cout << "The fourth smallest element is " << v[3] << '\n';
    return 0;
}

```

***partial_sort 和 nth_element 比较记忆***

    partial_sort 使得前 N 个元素按排序顺序排列，

    nth_element 只保证第 N 个元素位于其在完全排序序列中的正确位置，不保证其他元素的顺序

    选择指南：

       1. 如果你的目标是找到并排序序列中最小（或最大）的 N 个元素：partial_sort
      
       2. 如果你只需要找到位于序列特定位置（如中位数）的元素，而不关心序列的其他部分是否有序：nth_element

---


###### (4) 二分搜索操作（在有序序列上）

***lower_bound 和 upper_bound***

这两个函数用于在已排序的序列中查找某个值的边界

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 4, 4, 5};
    auto lower = lower_bound(v.begin(), v.end(), 4);
    auto upper = upper_bound(v.begin(), v.end(), 4);
    //跟max_element 和 min_element 一样, 返回的是迭代器

    cout << "Lower bound for 4: " << (lower - v.begin()) << '\n';
    //2(下界是指不小于给定值的第一个元素的位置)

    cout << "Upper bound for 4: " << (upper - v.begin()) << '\n';
    //4(上界是指大于给定值的第一个元素的位置)

    return 0;
}
```

---

***equal_range***

同时获取 lower_bound 和 upper_bound

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 3, 4, 5};
    auto range = equal_range(v.begin(), v.end(), 3);
    /*
    //不同于lower_bound()，upper_bound(), max_element 和 min_element 返回的是迭代器

    range 是一个 pair 类型的对象，它包含两个成员：first 和 second，它们都是迭代器.

    range 是一个 pair，其中 range.first 是指向第一个 3 的迭代器（lower_bound），
                        range.second 是指向第一个大于 3 的元素的迭代器（upper_bound）
    */

    cout << "3 is found in the range [" << (range.first - v.begin()) << ", " << (range.second - v.begin()) << ")" << '\n';
    //因为 range 是一个对象，而不是指针，所以应该使用 . 操作符来访问这些成员

    return 0;
}
```

---

***比较 lower_bound()，upper_bound()，max_element， min_element 和 equal_range***

1. 使用 -> ：当有一个指向对象的指针或类似于指针的迭代器，并且你需要访问该对象的成员

```cpp

auto max_it = max_element(m.begin(), m.end(), [](const pair<char, int> &a, const pair<char, int> &b){
    return a.second < b.second ;
    });

    max = max_it->second;
    //max_it 是一个指向 map 中元素的迭代器 map 的元素类型是 pair<const Key, T>
    //所以 max_it 指向一个 pair要访问 pair 的 second 成员，你需要先解引用迭代器，这可以通过 -> 操作符实现
    //解引用迭代器（*iter）访问元素的值，通过 -> 操作符可以直接访问元素的成员
```

2. 使用 . 当你直接操作一个对象实例，并且需要访问它的成员

```cpp
auto range = equal_range(v.begin(), v.end(), 3);
//不同于lower_bound()，upper_bound()，max_element 和 min_element 返回的是迭代器
//range 是一个 pair 类型的对象，它包含两个成员：first 和 second，它们都是迭代器.

cout << "3 is found in the range [" << (range.first - v.begin()) << ", " << (range.second - v.begin()) << ")" << '\n';
//因为 range 是一个对象，而不是指针，所以应该使用 . 操作符来访问这些成员
```

---

***binary_search***

检查序列中是否存在某个值

```cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};
    if (binary_search(v.begin(), v.end(), 3)) cout << "Found the element 3" << '\n';
    return 0;
}
```

***比较：关于 binary_search 和 find***

binary_search 和 find 都可以用于查找元素，但它们的用法和效率有所不同

***binary_search***

    1. 有序序列
    
    2. 如果存在：返回 true; 如果不存在： 返回 false 
    
    3. 使用二分查找时间复杂度是 O(log n)


***find***

    4. 无序或有序序列

    5. 如果找到：返回一个指向该元素的迭代器；如果没有找到：返回一个指向序列末尾的迭代器
    
    6. 时间复杂度是 O(n)


总的来说

    当序列是有序的，且只检查元素是否存在（不需要知道具体位置）——> 使用 binary_search 

    如果序列无序，或者需要元素的确切位置 ——> 使用 find

---

###### (5) 集合操作（在有序序列上）

***merge***

合并两个有序序列

```cpp

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {1, 3, 5};
    vector<int> v2 = {2, 4, 6};
    vector<int> result(v1.size() + v2.size());

    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
    /*
    注意有5个参数

    可以控制合并的范围，比如说merge(v1.begin() + 1, v1.end(), v2.begin() + 1, v2.end(), result.begin());

    输出的就是3 4 5 6 0 0 
    */

    for(int n : result) cout << n << ' ';
    //输出1 2 3 4 5 6 
    return 0;
}
```

---

***inplace_merge***

在原地合并两个有序序列

```cpp

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = {1, 3, 5, 2, 4, 6};
    // 假设前半部分和后半部分都已排序
    inplace_merge(v.begin(), v.begin() + 3, v.end());
    /*
    注意有三个参数

    只有3可以，因为只有以3为节点是两边的序列是有序的，写 v.begin() + 2等等都不行
    */
    for(int n : v) cout << n << ' ';
    //输出1 2 3 4 5 6 
    return 0;
}
```

---

***includes***

检查一个有序序列是否包含另一个序列

```cpp

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {2, 4};

    bool result = includes(v1.begin(), v1.end(), v2.begin(), v2.end());
    //注意是 includes 不是 include
    //可控范围

    cout << "Includes: " << result << '\n';
    //v1 包含 v2 输出 1, 否则输出 0
    //本例输出 1
    return 0;
}
```

---

***set_union, set_intersection, set_difference, set_symmetric_difference***

对两个集合执行集合操作

```cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {4, 5, 6, 7, 8};
    vector<int> result;

    // Union并集
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出1 2 3 4 5 6 7 8
    cout << "\n";
    result.clear();

    // Intersection交集
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出4 5
    cout << "\n";
    result.clear();

    // Difference差集(找出在 v1 中但不在 v2 中的元素)
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出1 2 3
    cout << "\n";
    result.clear();

    // Symmetric difference对称差集(找出仅出现在 v1 或 v2 中的元素)
    set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " ";// //输出1 2 3 6 7 8
    cout << "\n";
    result.clear();

    return 0;
}
```

---


###### (6) 最小/最大操作

***max, min***

返回两个值中的最大值或最小值

```cpp

#include <iostream>
#include <algorithm>

using namespace std;

int main() 
{
    cout << "Max: " << max(1, 2) << '\n';
    cout << "Min: " << min(1, 2) << '\n';

    return 0;
}
```

---

***max_element, min_element***

查找序列中的最大或最小元素

```cpp

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() 
{
    vector<int> v = {1, 5, 3};

    auto max_it = max_element(v.begin(), v.end());
    auto min_it = min_element(v.begin(), v.end());
    //注意无论是作用于 vector 还是 map，返回的都是一个迭代器

    cout << "Max element: " << *max_it << '\n';
    cout << "Min element: " << *min_it << '\n';
    //解引用迭代器（*iter）访问元素的值，而通过 -> 操作符可以直接访问元素的成员

    return 0;
}
```

[例](luogu/introduction_3/1598)

```cpp
auto max_it = max_element(m.begin(), m.end(), 
    [](const pair<char, int> &a, const pair<char, int> &b){return a.second < b.second ;});

    max = max_it->second;
```

```cpp
for(auto &i : m)
{
    max = max(max, i.second);
}
```

这两段代码实现相同目的，但 max_element 对 map 的处理需要多一个(第三个)参数,格式：[外部变量](待比较的参数){如何比较参数 ;}

max_it 是一个指向 map 中元素的迭代器, map 的元素类型是 pair<const Key, T>

所以 max_it 指向一个 pair要访问 pair 的 second 成员，你需要先解引用迭代器，这可以通过 -> 操作符实现

---

***clamp***（C++17 中引入）

将值限制在指定的范围内

```cpp

#include <iostream>
#include <algorithm>

using namespace std;

int main() 
{
    cout << "Clamped: " << clamp(5, 1, 10) << '\n'; // 5
    cout << "Clamped: " << clamp(-1, 1, 10) << '\n'; // 1
    return 0;
}

```

---

###### (7) 比较操作

***equal***

equal检查两个序列是否相等

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};

    bool isEqual = equal(v1.begin(), v1.end(), v2.begin());
    //可控范围
    //需要 v1.size() 大于等于 v2.size(), 否则如果 v1 是 v2 的子序列，也会输出1(true)
    //为避免这种情况,还是写成标准形式equal(v1.begin(), v1.end(), v2.begin(), v2.end());

    cout << "Equal: " << boolalpha << isEqual << '\n';
    return 0;
}
```

equal 是一个标准库算法，用于比较两个范围内的元素是否相等, 它可以接受一个二元谓词作为参数，用于自定义比较方式

`bool areEqual(int a, int b){return a == b;} // 二元谓词函数`

`bool result = equal(vec1.begin(), vec1.end(), vec2.begin(), areEqual);`

equal_to 是一个标准库函数对象，用于比较两个对象是否相等, 通常用于需要函数对象的地方，例如 STL 容器的比较操作

`bool result = equal(vec1.begin(), vec1.end(), vec2.begin(), equal_to<int>());`

    谓词: 是返回布尔值的可调用对象，用于条件检查或比较

    一元谓词, 接受一个参数; 二元谓词接受两个参数

---

***lexicographical_compare***

比较两个序列的字典顺序

```cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 4};

    bool result = lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

    cout << "v1 < v2: " << result << '\n';
    //v1 < v2 返回 1；
    //v1 > v2 返回 0
    return 0;
}
```

---

###### (8) 排列操作

***next_permutation 和 prev_permutation***

    按照字典序生成序列的下一个或上一个排列

    示例
    假设我们有一个序列{1, 2, 3}

    应用 next_permutation
    初始序列：{1, 2, 3}，下一个序列：{1, 3, 2}
    应用后：{1, 3, 2}，下一个序列：{2, 1, 3}

    继续应用直至返回到最初序列，生成所有可能的排列

```cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3};

    next_permutation(v.begin(), v.end());

    for(int n : v) cout << n << ' '; // 输出: 1 3 2
    cout << '\n';

    prev_permutation(v.begin(), v.end());

    for(int n : v) cout << n << ' '; // 输出: 1 2 3
    return 0;
}
```

放进循环输出所有的排列方式

```cpp

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

bool is_Palindrome(string ss)
{
  stack<char> st;
  int len = (ss.length() % 2 ? (ss.length() / 2 + 1) : ss.length() / 2);
  for (int i = len; i < ss.length(); i++)
    st.push(ss[i]);
  for (int i = 0; i < len && !st.empty(); i++)
  {
    if (ss[i] == st.top())
      st.pop();
    else
      return false;
  }
  return true;
}

int main()
{
  cout << "please input Palindrome string: ";
  string ss;
  cin >> ss;
  cout << "your input string is_Palindrome : " << is_Palindrome(ss) << endl; // 验证回文数函数

  vector<string> res;
  unsigned long long ans = 0;
  int cnt = 0;

  // 循环输出所有的排列方式
  sort(ss.begin(), ss.end()); // 先排序
  cout << ss << " ";
  while (next_permutation(ss.begin(), ss.end()))
  {
    ans++;
    cout << ss << " ";
    if (is_Palindrome(ss))
    {
      res.push_back(ss);
      cnt++;
    }
  }
  cout << endl;
  cout << "ways : " << ans + 1 << endl;
  for (string st : res)
    cout << st << " ";
  cout << endl;
  cout << "is_palindrome_num : " << cnt << endl;
  cout << "is_Palindrome('abcdba') : " << is_Palindrome("abcdba") << endl; // 验证回文数函数
  return 0;
}
```

#### 9. numeric

    <numeric> 头文件中包含了一系列用于执行数值操作的模板函数
    这些函数包括执行累加, 求和, 内积, 部分和, 相邻差, 扫描(inclusive 和 exclusive), GCD/LCM 计算等

##### 算法列表及代码实现

！！！注意：一些函数（如 reduce, inclusive_scan, exclusive_scan, gcd 和 lcm）是在 C++17 引入，请确定编译器是否支持 c++17

###### accumulate

计算给定范围内所有元素的和，也可以提供一个初始值

```cpp
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};

    int sum = accumulate(v.begin(), v.end(), 0);

    cout << "Sum: " << sum << endl; 
    // 输出: Sum: 15
}
```

---

###### inner_product

计算两个范围的内积（点积）

```cpp

#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5, 6};
    // b.size() 要大于或等于 a.size() , 否则会出现位置的结果(比如说 -1364283718)

    int product = inner_product(a.begin(), a.end(), b.begin(), 0);

    cout << "Inner product: " << product << endl; 
    // 输出: 32
}
```

---

###### adjacent_difference

计算序列中相邻元素的差

```cpp

#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> v = {1, 3, 6, 10};
    vector<int> diff;

    adjacent_difference(v.begin(), v.end(), back_inserter(diff));
    /*
    在同一个向量 v 的末尾插入计算结果(agjacent_difference(v.begin(), v.end(), back_inserter(v));)
    当 adjacent_difference 开始向 v 添加元素时，v 的大小开始增长
    这意味着，如果在遍历过程中向容器添加更多元素，v.end() 可能会改变，导致未定义行为

    为了避免这种问题，应该避免在使用算法处理容器时，向同一个容器追加元素
    一个更安全的做法是使用一个单独的向量来存储结果 (比如说 diff)
    */

    for (auto d : diff)
    {
        cout << d << " "; 
    } 
    // 输出: 1 2 3 4
    
    cout << endl;
}
```

---

###### partial_sum

计算给定范围内每个元素的部分和

```cpp
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

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
```

---


###### iota

在指定范围内生成连续的递增（或递减）值

```cpp
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

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
```

---

***reduce (C++17)***

类似于 accumulate，但不保证顺序执行，允许并行化处理

```cpp
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};

    int sum = reduce(execution::par, v.begin(), v.end());

    cout << "Sum: " << sum << endl; // 输出取决于实现，但通常是 15
}
注意：使用 reduce 需要包含 <execution> 头文件，并确保编译器支持 C++17 或更高版本

```

---

***inclusive_scan 和 exclusive_scan (C++17) ***

分别计算给定范围内的包含式和排他式扫描（部分和）

```cpp
#include <numeric>
#include <vector>
#include <iostream>

using namesapce std;

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
```

---

###### gcd 和 lcm (C++17)

分别计算两个数的最大公约数和最小公倍数

```cpp

#include <numeric>
#include <iostream>

using namespace std;

int main() 
{
    cout << "gcd(20, 30): " << gcd(20, 30) << endl; // 输出: 10
    cout << "lcm(6, 8): " << lcm(6, 8) << endl; // 输出: 24
}
```

---

### 五、内存管理

#### 10. memory

提供了智能指针和内存管理工具，帮助开发者更安全地管理动态内存，避免内存泄漏和悬挂指针等问题

##### 常用组件用法及示例代码

###### unique_ptr

***独占所有权***

unique_ptr 是一种独占所有权的智能指针, 当它被销毁时, 自动释放所管理的对象

```cpp
#include <iostream>
#include <memory>

using namespace std;

int main() 
{
    // 创建一个 unique_ptr 管理的动态分配的 int
    unique_ptr<int> ptr1(new int(10));
    cout << "Value: " << *ptr1 << endl;

    // 使用 make_unique 创建 unique_ptr
    auto ptr2 = make_unique<int>(20);
    cout << "Value: " << *ptr2 << endl;

    // 转移所有权
    unique_ptr<int> ptr3 = move(ptr1);
    if (!ptr1) {
        cout << "ptr1 is now null" << endl;
    }
    cout << "Value: " << *ptr3 << endl;

    return 0;

    /*
    输出：
        Value: 10
        Value: 20
        ptr1 is now null
        Value: 10
    */
}
```

---


###### shared_ptr

***共享所有权***

shared_ptr 是一种共享所有权的智能指针, 通过引用计数来管理共享所有权的对象

```cpp
#include <iostream>
#include <memory>

using namespace std;

int main() 
{
    // 创建一个 shared_ptr 管理的动态分配的 int
    shared_ptr<int> ptr1(new int(10));
    cout << "Value: " << *ptr1 << ", use count: " << ptr1.use_count() << endl;

    // 使用 make_shared 创建 shared_ptr
    auto ptr2 = make_shared<int>(20);
    cout << "Value: " << *ptr2 << ", use count: " << ptr2.use_count() << endl;

    // 共享所有权
    shared_ptr<int> ptr3 = ptr1;
    cout << "Value: " << *ptr1 << ", use count: " << ptr1.use_count() << endl;
    cout << "Value: " << *ptr3 << ", use count: " << ptr3.use_count() << endl;

    return 0;
    /*
    输出：
        Value: 10, use count: 1
        Value: 20, use count: 1
        Value: 10, use count: 2
        Value: 10, use count: 2
    */
}
```

---

###### weak_ptr

weak_ptr 是一种不拥有对象所有权的智能指针， 防止 shared_ptr 循环引用

```cpp

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    shared_ptr<int> sharedPtr = make_shared<int>(10);
    weak_ptr<int> weakPtr = sharedPtr;

    cout << "Shared use count: " << sharedPtr.use_count() << endl;

    if (auto sp = weakPtr.lock())
    {
        cout << "Weak pointer is valid, value: " << *sp << endl;
    }
    else
    {
        cout << "Weak pointer is expired" << endl;
    }

    sharedPtr.reset(); // 释放 shared_ptr

    if (auto sp = weakPtr.lock())
    {
        cout << "Weak pointer is valid, value: " << *sp << endl;
    }
    else
    {
        cout << "Weak pointer is expired" << endl;
    }

    return 0;
}
```

---

###### allocator

allocator 提供了一个用于动态分配内存的类模板
虽然在现代 C++ 中它很少直接使用，但它仍然是理解 STL 容器的内存管理的关键

```cpp
#include <iostream>
#include <memory>

using namespace std;

int main() 
{
    allocator<int> alloc; // 创建一个分配器对象

    // 分配内存但不构造对象
    int* p = alloc.allocate(1);

    // 在分配的内存上构造对象
    alloc.construct(p, 42);

    cout << "Value: " << *p << endl;

    // 销毁对象但不释放内存
    alloc.destroy(p);

    // 释放内存
    alloc.deallocate(p, 1);

    return 0;
}
```

---


###### pointer_traits

pointer_traits 是一个模板类, 为指针类型提供了类型特征信息, 主要用于泛型编程

```cpp
#include <iostream>
#include <memory>

using namespace std;

int main() 
{
    using Ptr = unique_ptr<int>;
    using Traits = pointer_traits<Ptr>;

    Ptr p = make_unique<int>(42);
    cout << "Pointer value: " << *p << endl;
    //Pointer value: 42
    cout << "Pointer element type: " << typeid(Traits::element_type).name() << endl;
    //Pointer element type: i

    return 0;
}
```

---

###### uninitialized_copy 和 uninitialized_fill

这些函数用于在未初始化的内存中构造对象

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5};
    int *p = static_cast<int *>(::operator new(sizeof(int) * vec.size()));

    // 使用 uninitialized_copy 在未初始化的内存中构造对象
    uninitialized_copy(vec.begin(), vec.end(), p);

    // 打印复制的对象
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << p[i] << " ";
    }
    //1 2 3 4 5 
    cout << endl;

    // 使用 uninitialized_fill 在未初始化的内存中构造对象
    uninitialized_fill(p, p + vec.size(), 10);

    // 打印填充的对象
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << p[i] << " ";
    }
    //10 10 10 10 10
    cout << endl;

    // 手动销毁对象
    destroy(p, p + vec.size());

    // 释放内存
    ::operator delete(p);

    return 0;
}
```

---

###### align

align 是一个用于对齐内存块的函数

```cpp
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    alignas(16) char buffer[64]; // 确保 buffer 对齐到 16 字节
    void *ptr = buffer;

    size_t space = sizeof(buffer);
    void *aligned_ptr = align(16, sizeof(int), ptr, space);

    if (aligned_ptr)
    {
        cout << "Aligned pointer: " << aligned_ptr << endl;
        cout << "Remaining space: " << space << endl;
    }
    else
    {
        cout << "Alignment failed" << endl;
    }

    return 0;
}
```

---

###### raw_storage_iterator

raw_storage_iterator 是一个适配器, 用于将未初始化的内存视为输出迭代器

```cpp
#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

using namespace std;

int main() 
{
    int buffer[4];
    raw_storage_iterator<int*, int> iter(buffer);

    *iter++ = 1;
    *iter++ = 2;
    *iter++ = 3;
    *iter++ = 4;
    /*
    相当于：
    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;
    */

    for (int i : buffer) 
    {
        cout << i << " ";
    }
    //1 2 3 4
    cout << endl;

    return 0;
}
```

---

### 六、迭代器

#### 11. iterator

##### 常用组件用法及示例代码

###### iterator_traits

iterator_traits 是一个模板类，用于提取迭代器的属性类型 (如 value_type, difference_type, pointer, reference 和 iterator_category)

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() 
{
    using Iterator = vector<int>::iterator;
    iterator_traits<Iterator>::value_type x = 5; // x 是 int 类型
    cout << "Value type: " << typeid(x).name() << endl;
    //Value type: i
    return 0;
}
```

---

###### distance

distance 用于计算两个迭代器之间的距离

distance() 可以用于任何类型的迭代器，包括输入迭代器和前向迭代器，而直接相减仅适用于随机访问迭代器

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    auto distance = distance(vec.begin(), vec.end());
    cout << "Distance: " << distance << endl; // 输出 5
    return 0;
}
```

---

###### advance

advance 用于将迭代器前进特定的距离

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace tsd;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin();
    advance(it, 3);
    cout << "Iterator advanced to: " << *it << endl; // 输出 4
    return 0;
}
```

---

###### next 和 prev

next 和 prev 分别用于获取迭代器前进或后退指定距离后的新迭代器

next() 和 prev() 返回一个新的迭代器，而不修改原始迭代器
直接对迭代器进行加减操作会修改原始迭代器

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = next(vec.begin(), 3);
    cout << "Next iterator points to: " << *it << endl; // 输出 4

    it = prev(vec.end(), 2);
    cout << "Prev iterator points to: " << *it << endl; // 输出 4
    return 0;
}
```

---

###### back_inserter, front_inserter 和 inserter

这些函数返回插入迭代器, 它们用于在容器的特定位置插入元素

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3};
    list<int> lst;

    // back_inserter
    copy(vec.begin(), vec.end(), back_inserter(lst));
    for (int n : lst) 
        cout << n << " "; // 输出 1 2 3
    cout << endl;

    // front_inserter
    copy(vec.begin(), vec.end(), front_inserter(lst));
    for (int n : lst) 
        cout << n << " "; // 输出 3 2 1 1 2 3
    cout << endl;

    // inserter
    auto it = lst.begin();
    advance(it, 3);
    copy(vec.begin(), vec.end(), inserter(lst, it));
    for (int n : lst) 
        cout << n << " "; // 输出 3 2 1 1 2 3 1 2 3
    cout << endl;

    return 0;
}
```

---

###### 补充知识：工厂函数

    back_inserter() 是一个简便的工厂函数, 用于创建 back_insert_iterator

    back_inserter(vec2) 创建了一个 back_insert_iterator<vector<int>>
    
    它们在功能上是等价的

    (同理 front_inserter(v) 和 front_insert_iterator<vector<int>>(v))
    (同理 insert_iterator(v, it) 和 insert_iterator<vector<int>>(v, it))

---

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3};
    vector<int> v;
    list<int> l;

    // back_insert_iterator<vector<int>> (v)
    copy(vec.begin(), vec.end(), back_insert_iterator<vector<int>>(v));
    cout << "v:\n";
    for (int n : v) 
        cout << n << " "; // 输出 1 2 3
    cout << endl;

    // insert_iterator<vector<int>>(v, v.begin())
    copy(vec.begin(), vec.end(), insert_iterator<vector<int>>(v, v.begin()));
    cout << "v:\n";
    for (int n : v) 
        cout << n << " "; // 输出 1 2 3 1 2 3
    cout << endl;

    // front_insert_iterator<vector<int>>(v)
    copy(vec.begin(), vec.end(), front_insert_iterator<list<int>>(l));
    cout << "l:\n";
    for (int n : l) 
        cout << n << " "; // 输出 3 2 1
    cout << endl;

    return 0;
}
```

###### ostream_iterator 和 istream_iterator

用于从输出流和输入流进行迭代

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};

    // ostream_iterator
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl; // 输出 1 2 3 4 5

    // istream_iterator
    vector<int> vec2;
    cout << "Enter numbers (non-number to end): ";
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec2));
    //Enter numbers (non-number to end): 1 5 2 4 3

    cout << "You entered: ";
    copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
    //You entered: 1 5 2 4 3
    cout << endl;

    return 0;
}
```

---

###### reverse_iterator

用于反向迭代

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    reverse_iterator<vector<int>::iterator> rit = vec.rbegin();
    for (; rit != vec.rend(); ++rit) {
        cout << *rit << " "; // 输出 5 4 3 2 1
    }
    cout << endl;
    return 0;
}
```

---

###### move_iterator

用于将普通迭代器转换为移动迭代器

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    vector<string> vec = {"one", "two", "three"};
    vector<string> vec2;

    // move_iterator
    move(vec.begin(), vec.end(), back_inserter(vec2));
    for (const auto& str : vec2) 
    {
        cout << str << " "; // 输出 one two three
    }
    cout << endl;

    return 0;
}
```

---

### 七、实用工具

#### 12. utility

提供了一系列实用程序组件，包括配对对象、交换操作、移动语义以及辅助功能。


##### 常用组件用法及示例代码

###### pair:

pair 是一个结构，它可以存储两个可能不同类型的值。这在需要将两个值视为一个单元时非常有用。

```cpp
#include <utility>
#include <iostream>
#include <string>

using namespace std;

int main() 
{
    pair<int, string> p = {1, "apple"};

    cout << "The pair is: (" << p.first << ", " << p.second << ")\n";

    return 0;
}
```

---

###### make_pair:

make_pair 是一个辅助函数，用于创建 pair 对象，其类型由传递给它的参数推断出来。

```cpp
#include <utility>
#include <iostream>

using namespace std;

int main() 
{
    auto p = make_pair(42, "hello");

    cout << "The pair contains: " << p.first << " and " << p.second << "\n";

    return 0;
}
```

---

###### move:

move 将其参数转换为右值引用，允许移动语义而不是复制。

```cpp

#include <utility>
#include <vector>
#include <iostream>

using namespace std;

int main() 
{
    vector<int> src = {1, 2, 3};
    vector<int> dest = move(src); // Moves the contents of src to dest

    cout << "src size after move: " << src.size() << '\n'; // src is now empty
    cout << "dest has " << dest.size() << " elements.\n";

    return 0;
}
```

---


###### swap:

swap 交换两个对象的值。

```cpp
#include <utility>
#include <iostream>

using namespace std;

int main() 
{
    int a = 5, b = 10;
    swap(a, b);

    cout << "a is " << a << ", b is " << b << "\n";

    return 0;
}
```

---

###### forward

forward 用于实现完美转发，它可以保持对象的左值或右值属性。

```cpp

#include <utility>
#include <iostream>

using namespace std;

void overloaded(int &arg) 
{ 
    cout << "by lvalue\n"; 
}

void overloaded(int &&arg) 
{ 
    cout << "by rvalue\n"; 
}

template <typename T>
void forwarding(T &&arg) //万能引用（T&&）
{
    overloaded(forward<T>(arg));
}

int main() 
{
    int x = 5;

    forwarding(x); // lvalue
    forwarding(3); // rvalue

    return 0;
}
```

---

###### declval

declval 用于在不构造对象的情况下获得对象类型的引用，主要用于模板元编程和类型推导。

```cpp

#include <utility>
#include <type_traits>

using namespace std;

template <typename T>
void foo(const T &) 
{
    static_assert(is_same<decltype(declval<T>()), T&&>::value, "T must be deducible to T&&");
}
```

---

###### tie

tie 可以创建一个 tuple 的引用包装器，这常用于解构 pair 或 tuple

```cpp
#include <utility>
#include <tuple>
#include <iostream>

using namespace std;

int main() 
{
    pair<int, string> p = make_pair(2, "pear");
    int num;
    string fruit;

    tie(num, fruit) = p; // Unpack the pair into two variables

    cout << num << " " << fruit << '\n';

    return 0;
}
```

###### ignore

ignore 是一个特殊的对象，用以忽略 tie 的某个位置。

```cpp

#include <utility>
#include <tuple>
#include <iostream>

using namespace std;

int main()  
{
    tuple<int, double, string> t = make_tuple(1, 3.14, "apple");
    int i;
    string s;

    tie(i, ignore, s) = t; // Ignore the double in the middle

    cout << i << " and " << s << '\n';

    return 0;
}
```

---

### 八、函数相关 

#### 13. functional

允许创建和操作函数对象

##### 常用组件用法及示例代码

###### function

function 是一个通用, 多态的函数包装器
它可以持有任何可调用的目标： 普通函数， lambda 表达式， 绑定表达式或函数对象

```cpp

#include <iostream>
#include <functional>

using namespace std;

void freeFunction(int a)
{
    cout << "Free function called with " << a << endl;
}

class Functor
{
public:
    void operator()(int a) const
    {
        cout << "Functor called with " << a << endl;
    }
};

int main()
{
    function<void(int)> func;

    // 使用普通函数
    func = freeFunction;
    func(10);

    // 使用 lambda 表达式
    func = [](int a)
    {
        cout << "Lambda called with " << a << endl;
    };
    func(20);

    // 使用函数对象
    Functor functor;
    func = functor;
    func(30);

    return 0;
}
```

---


###### bind

bind 创建一个新的函数对象, 将一些参数绑定到现有的函数或函数对象上

```cpp

#include <iostream>
#include <functional>

using namespace std;

void freeFunction(int a, int b) 
{
    cout << "Free function called with " << a << " and " << b << endl;
}

int main() 
{
    auto boundFunc = bind(freeFunction, placeholders::_1, 42);

    boundFunc(10); // 实际调用 freeFunction(10, 42)

    return 0;
}
```

---

###### mem_fn

mem_fn 生成一个可调用对象来调用成员函数或访问成员变量

```cpp
#include <iostream>
#include <functional>

using namespace std;

class MyClass 
{
public:
    void memberFunction(int a) const 
    {
        cout << "Member function called with " << a << endl;
    }
};

int main() {
    MyClass obj;

    auto memFunc = mem_fn(&MyClass::memberFunction);
    memFunc(&obj, 10); // 等价于 obj.memberFunction(10)

    return 0;
}
```

---
标准函数对象

---

###### multiplies

multiplies 是一个函数对象，用于执行乘法运算

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    multiplies<int> multiply;
    int result = multiply(10, 2);
    cout << "10 * 2 = " << result << endl;

    return 0;
}
```

---

###### divides

divides 是一个函数对象，用于执行除法运算

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    divides<int> divide;
    int result = divide(10, 2);
    cout << "10 / 2 = " << result << endl;

    return 0;
}
```

---

###### modulus

modulus 是一个函数对象， 用于执行取模（余数）运算

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    modulus<int> mod;
    int result = mod(10, 3);
    cout << "10 % 3 = " << result << endl;

    return 0;
}
```

---


###### equal_to

equal_to 是一个函数对象，用于检查两个值是否相等

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    equal_to<int> equal;
    bool result = equal(10, 10);
    cout << "10 == 10: " << boolalpha << result << endl;

    result = equal(10, 20);
    cout << "10 == 20: " << boolalpha << result << endl;

    return 0;
}
```

---

###### not_equal_to

not_equal_to 是一个函数对象，用于检查两个值是否不相等

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    not_equal_to<int> not_equal;
    bool result = not_equal(10, 20);
    cout << "10 != 20: " << boolalpha << result << endl;

    result = not_equal(10, 10);
    cout << "10 != 10: " << boolalpha << result << endl;

    return 0;
}
```

---

###### less

less 是一个函数对象，用于检查左操作数是否小于右操作数。

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    less<int> less_than;
    bool result = less_than(10, 20);
    cout << "10 < 20: " << boolalpha << result << endl;

    result = less_than(20, 10);
    cout << "20 < 10: " << boolalpha << result << endl;

    return 0;
}
```

---

###### greater

greater 是一个函数对象，用于检查左操作数是否大于右操作数

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main()
{
    greater<int> greater_than;
    bool result = greater_than(20, 10);
    cout << "20 > 10: " << boolalpha << result << endl;

    result = greater_than(10, 20);
    cout << "10 > 20: " << boolalpha << result << endl;

    return 0;
}
```

---

###### less_equal

less_equal 是一个函数对象，用于检查左操作数是否小于或等于右操作数

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    less_equal<int> less_equal_to;
    bool result = less_equal_to(10, 20);
    cout << "10 <= 20: " << boolalpha << result << endl;

    result = less_equal_to(20, 20);
    cout << "20 <= 20: " << boolalpha << result << endl;

    return 0;
}
```

---

###### greater_equal

greater_equal 是一个函数对象，用于检查左操作数是否大于或等于右操作数

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    greater_equal<int> greater_equal_to;
    bool result = greater_equal_to(20, 10);
    cout << "20 >= 10: " << boolalpha << result << endl;

    result = greater_equal_to(20, 20);
    cout << "20 >= 20: " << boolalpha << result << endl;

    return 0;
}
```

---

###### logical_and

logical_and 是一个函数对象，用于执行逻辑与操作

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    logical_and<bool> logical_and;
    bool result = logical_and(true, false);
    cout << "true && false: " << boolalpha << result << endl;

    result = logical_and(true, true);
    cout << "true && true: " << boolalpha << result << endl;

    return 0;
}
```

---

###### logical_or

logical_or 是一个函数对象，用于执行逻辑或操作

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    logical_or<bool> logical_or;
    bool result = logical_or(true, false);
    cout << "true || false: " << boolalpha << result << endl;

    result = logical_or(false, false);
    cout << "false || false: " << boolalpha << result << endl;

    return 0;
}
```

---

###### logical_not

logical_not 是一个函数对象，用于执行逻辑非操作

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() 
{
    logical_not<bool> logical_not;
    bool result = logical_not(true);
    cout << "!true: " << boolalpha << result << endl;

    result = logical_not(false);
    cout << "!false: " << boolalpha << result << endl;

    return 0;
}
```

---

###### negate

negate 是一个函数对象，用于对数值执行取负操作

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main()
{
    negate<int> negate;
    int result = negate(10);
    cout << "Negate 10: " << result << endl;

    return 0;
}
```

---

***使用函数对象与标准算法结合***

例：使用 accumulate 计算一个数组元素的乘积：

```cpp
#include <iostream>
#include <vector>
#include <numeric> // for accumulate
#include <functional>

using namespace std;

int main() 
{
    vector<int> numbers = {1, 2, 3, 4, 5};

    //使用 multiplies<int> 作为二元操作函数对象来计算数组中所有元素的乘积
    int product = accumulate(numbers.begin(), numbers.end(), 1, multiplies<int>());

    cout << "Product of elements: " << product << endl;

    return 0;
}
```

---

###### invoke

invoke 用于调用任何可调用对象，它可以是函数指针，成员函数指针，函数对象或 lambda 表达式

```cpp
#include <iostream>
#include <functional>

using namespace std;

void freeFunction(int a)
{
    cout << "Free function called with " << a << endl;
}

int main()
{
    // 使用 invoke 调用普通函数
    invoke(freeFunction, 10);

    // 使用 invoke 调用 lambda 表达式
    auto lambda = [](int a)
    {
        cout << "Lambda called with " << a << endl;
    };
    invoke(lambda, 20);

    // 使用 invoke 调用成员函数
    class MyClass
    {
    public:
        void memberFunction(int a) const
        {
            cout << "Member function called with " << a << endl;
        }
    };

    MyClass obj;
    invoke(&MyClass::memberFunction, obj, 30);

    return 0;
}
```

---

###### not_fn

not_fn 返回一个逻辑否定函数对象，可以用于对其他可调用对象的结果取反

```cpp
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};

    auto is_even = [](int n) 
    {
        return n % 2 == 0;
    };

    auto is_odd = not_fn(is_even);

    cout << "Odd numbers: ";
    for (int n : vec) 
    {
        if (is_odd(n)) 
        {
            cout << n << " ";
        }
    }
    //Odd numbers: 1 3 5 
    cout << endl;

    return 0;
}
```

---

###### reference_wrapper

reference_wrapper 用于创建对象的引用包装器, 可以在需要传递对象引用而非拷贝的地方使用

```cpp
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

void print(int& n) 
{
    cout << n << endl;
}

int main() {
    int x = 10;
    vector<reference_wrapper<int>> vec;
    vec.push_back(x);

    for (auto& ref : vec) 
    {
        print(ref);
    }

    return 0;
}
```

---

###### hash

hash 提供了对标准库中各种类型的哈希支持，常用于哈希表 (如 unordered_map 和 unordered_set)

```cpp
#include <iostream>
#include <functional>
#include <string>

using namespace std;

int main() 
{
    // 对整数进行哈希计算
    hash<int> hash_int;
    int int_value = 42;
    size_t int_hash = hash_int(int_value);
    cout << "Hash of int 42: " << int_hash << endl;

    // 对字符串进行哈希计算
    hash<string> hash_string;
    string str_value = "hello";
    size_t str_hash = hash_string(str_value);
    cout << "Hash of string 'hello': " << str_hash << endl;

    // 对浮点数进行哈希计算
    hash<double> hash_double;
    double double_value = 3.14;
    size_t double_hash = hash_double(double_value);
    cout << "Hash of double 3.14: " << double_hash << endl;

    return 0;
}
```

---
***深入探讨哈希函数***

---

    在 C++ 中, 哈希函数通常用于将数据映射到固定大小的整数值, 这些整数值通常用于快速查找, 存储和检索数据

    C++ 标准库提供了一个 hash 模板类, 可以对内置类型和部分标准库类型进行哈希操作

---

1. 自定义类型的哈希函数
   
    对于用户自定义的类型, 需要自定义哈希函数

```cpp
#include <iostream>
#include <functional>
#include <string>

struct Person
{
    string name;
    int age;

    bool operator==(const Person &other) const
    {
        return name == other.name && age == other.age;
    }
};

namespace std
{
    template <>
    struct hash<Person>
    {
        size_t operator()(const Person &p) const
        {
            size_t h1 = hash<string>{}(p.name);
            size_t h2 = hash<int>{}(p.age);
            return h1 ^ (h2 << 1); // 组合哈希值
        }
    };
}

int main()
{
    Person person = {"Alice", 30};
    hash<Person> hash_person;
    size_t person_hash = hash_person(person);
    cout << "Hash of Person {name: 'Alice', age: 30}: " << person_hash << endl;

    return 0;
}
```

---

2. 在标准容器中使用哈希函数
   
    哈希函数在标准容器(如 unordered_set 和 unordered_map)中非常有用
 
```cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() 
{
    unordered_map<string, int> umap;

    // 插入一些键值对
    umap["apple"] = 1;
    umap["banana"] = 2;
    umap["orange"] = 3;

    // 查找并输出元素
    string key = "banana";
    if (umap.find(key) != umap.end()) 
    {
        cout << key << ": " << umap[key] << endl;
    } 
    else 
    {
        cout << key << " not found in the map." << endl;
    }

    return 0;
}
```

3. 对自定义类型使用 unordered_map
   
    继续使用前面的 Person 结构体

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

// Person 结构体定义和哈希函数定义（与前面相同）
struct Person
{
    string name;
    int age;

    bool operator==(const Person &other) const
    {
        return name == other.name && age == other.age;
    }
};

namespace std
{
    template <>
    struct hash<Person>
    {
        size_t operator()(const Person &p) const
        {
            size_t h1 = hash<string>{}(p.name);
            size_t h2 = hash<int>{}(p.age);
            return h1 ^ (h2 << 1); // 组合哈希值
        }
    };
}

int main()
{
    unordered_map<Person, string> person_map;

    // 插入一些条目
    person_map[{"Alice", 30}] = "Engineer";
    person_map[{"Bob", 25}] = "Designer";

    // 查找并输出元素
    Person key = {"Alice", 30};
    if (person_map.find(key) != person_map.end())
    {
        cout << "Person {name: 'Alice', age: 30} is an " << person_map[key] << endl;
    }
    else
    {
        cout << "Person {name: 'Alice', age: 30} not found in the map." << endl;
    }

    return 0;
}
```