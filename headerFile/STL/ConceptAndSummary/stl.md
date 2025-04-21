## STL 6大组件

### 一、 容器 Container 
    
各种存放数据的数据结构： 

1. ***序列容器（Sequence Containers）***：元素按顺序存储，可以随机访问

    （1）vector：动态数组

    （2）deque：双端队列

    （3）list：双向链表

    （4）array：固定大小的数组（C++11 引入）

    （5）forward_list：单向链表（C++11 引入）
    
2. ***关联容器（Associative Containers）***：元素根据某个特定规则（如键值对）进行排序

    （1）set：集合，存储唯一元素，自动排序

    （2）map：映射（字典），存储键值对，按键排序

    （3）multiset：多重集合，可以存储重复元素

    （4）multimap：多重映射，可以存储具有相同键的多个值

3. ***无序容器（Unordered Containers）（C++11 引入）***：

    （1）unordered_set：无序集合

    （2）unordered_map：无序映射

    （3）unordered_multiset：无序多重集合

    （4）unordered_multimap：无序多重映射

### 二、算法 Algorithm 

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

这些算法是与容器分离的，可以独立于容器实现，通过迭代器与容器进行交互

### 三、 迭代器 Iterator 

***迭代器是 STL 的核心，容器与算法之间通过迭代器进行关联，提供对容器元素的统一访问方式***

迭代器像指针一样工作，但比指针更加灵活，支持不同类型的容器，其***本质是泛型指针***

常见的迭代器类型：

1. 输入迭代器：用于读取容器中的元素。

2. 输出迭代器：用于写入容器中的元素。

3. 前向迭代器：支持单向遍历。

4. 双向迭代器：支持双向遍历。

5. 随机访问迭代器：支持通过下标访问容器元素，具有与数组类似的访问方式

### 四、 仿函数 Function Object （函数对象（Functors）） 

定义：仿函数通过定义 operator() 成员函数,将一个类的对象变成可调用的函数对象

函数对象与算法配合使用，提供自定义的操作（如比较器、加法器等）。 

例如，sort 可以使用自定义的比较函数对象来决定如何排序：

```cpp
struct Compare {
    bool operator()(int a, int b) {
        return a < b;
    }
};

vector<int> v = {4, 1, 3, 2};
sort(v.begin(), v.end(), Compare());
```

### 五、适配器 Adaptor 

用于修饰容器，仿函数， 迭代器接口

1. 容器适配器：

    （1）stack（栈）

    （2）queue（队列）

    （3）priority_queue（优先队列）

2. 迭代器适配器：

    （1）reverse_iterator（反向迭代器）

    （2）back_insert_iterator（后插入迭代器）

    （3）front_insert_iterator（前插入迭代器）

    （4）insert_iterator（插入迭代器）

3. 函数适配器：

    （1）bind（在 C++11 中替代了旧的 bind1st 和 bind2nd）

    （2）mem_fn（成员函数适配器）

    （3）not1，not2（否定谓词）

```cpp
// bind
#include <iostream>
#include <functional> // 包含 bind
#include <vector>
#include <algorithm>

using namespace std;

void print_sum(int a, int b)
{
  cout << "Sum: " << a + b << endl;
}

int main()
{
  // 使用 bind 创建新的函数对象，固定参数 5
  auto bound_func = bind(print_sum, 5, placeholders::_1);

  // 使用绑定后的函数对象
  bound_func(10); // 输出 "Sum: 15"

  return 0;
```

```cpp
// mem_fn
#include <iostream>
#include <functional> // 包含 mem_fn
#include <vector>
#include <algorithm>

using namespace std;

class Person
{
public:
  Person(string name, int age) : name(name), age(age) {}
  void display() const
  {
    cout << name << " is " << age << " years old." << endl;
  }

private:
  string name;
  int age;
};

int main()
{
  vector<Person> people = {
      Person("Alice", 30),
      Person("Bob", 25),
      Person("Charlie", 35)};

  // 使用 mem_fn 将成员函数转化为可调用对象
  for_each(people.begin(), people.end(), mem_fn(&Person::display));

  return 0;
}
```

```cpp
//not1，not2
#include <iostream>
#include <functional> // 包含 std::not1 和 std::not2
#include <vector>
#include <algorithm>

bool is_odd(int n)
{
  return n % 2 != 0;
}

int main()
{
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // 使用 not1 适配器取反 is_odd 函数
  auto not_odd = std::not1(std::ptr_fun(is_odd));

  // 使用 std::remove_if 来删除所有偶数元素
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(), not_odd), numbers.end());

  // 打印结果
  for (int n : numbers)
  {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  return 0;
}
```

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
