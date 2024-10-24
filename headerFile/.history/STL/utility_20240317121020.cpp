<utility> 头文件在 C++ 标准库中提供了一系列实用程序组件，包括配对对象、交换操作、移动语义以及辅助功能。
以下是 <utility> 中定义的一些主要组件及其用法：

1. std::pair:
std::pair 是一个结构，它可以存储两个可能不同类型的值。这在需要将两个值视为一个单元时非常有用。

#include <utility>
#include <iostream>
#include <string>

int main() 
{
    std::pair<int, std::string> p = {1, "apple"};

    std::cout << "The pair is: (" << p.first << ", " << p.second << ")\n";

    return 0;
}


2. std::make_pair:
std::make_pair 是一个辅助函数，用于创建 std::pair 对象，其类型由传递给它的参数推断出来。

#include <utility>
#include <iostream>

int main() 
{
    auto p = std::make_pair(42, "hello");

    std::cout << "The pair contains: " << p.first << " and " << p.second << "\n";

    return 0;
}


#include <vector>
#include <utility> // for std::pair
#include <iostream>

int main() 
{
    std::vector<std::pair<int, char>> vec = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

    // Adding a new pair
    vec.push_back(std::make_pair(4, 'd'));

    // Iterating over the vector and printing its content
    for (const auto& p : vec) 
    {
        std::cout << p.first << ": " << p.second << '\n';
    }
}


3. std::move:
std::move 将其参数转换为右值引用，允许移动语义而不是复制。

#include <utility>
#include <vector>
#include <iostream>

int main() 
{
    std::vector<int> src = {1, 2, 3};
    std::vector<int> dest = std::move(src); // Moves the contents of src to dest

    std::cout << "src size after move: " << src.size() << '\n'; // src is now empty
    std::cout << "dest has " << dest.size() << " elements.\n";

    return 0;
}


4. std::swap:
std::swap 交换两个对象的值。

#include <utility>
#include <iostream>

int main() 
{
    int a = 5, b = 10;
    std::swap(a, b);

    std::cout << "a is " << a << ", b is " << b << "\n";

    return 0;
}


5. std::forward:
std::forward 用于实现完美转发，它可以保持对象的左值或右值属性。

#include <utility>
#include <iostream>

void overloaded(int &arg) 
{ 
    std::cout << "by lvalue\n"; 
}

void overloaded(int &&arg) 
{ 
    std::cout << "by rvalue\n"; 
}

template <typename T>
void forwarding(T &&arg) 
{
    overloaded(std::forward<T>(arg));
}

int main() 
{
    int x = 5;

    forwarding(x); // lvalue
    forwarding(3); // rvalue

    return 0;
}


6. std::declval:
std::declval 用于在不构造对象的情况下获得对象类型的引用，主要用于模板元编程和类型推导。

#include <utility>
#include <type_traits>

template <typename T>
void foo(const T &) 
{
    static_assert(std::is_same<decltype(std::declval<T>()), T&&>::value, "T must be deducible to T&&");
}


7. std::tie:
std::tie 可以创建一个 std::tuple 的引用包装器，这常用于解构 std::pair 或 std::tuple。

#include <utility>
#include <tuple>
#include <iostream>

int main() 
{
    std::pair<int, std::string> p = std::make_pair(2, "pear");
    int num;
    std::string fruit;

    std::tie(num, fruit) = p; // Unpack the pair into two variables

    std::cout << num << " " << fruit << '\n';

    return 0;
}


8. std::ignore:
std::ignore 是一个特殊的对象，用以忽略 std::tie 的某个位置。

#include <utility>
#include <tuple>
#include <iostream>

int main()  
{
    std::tuple<int, double, std::string> t = std::make_tuple(1, 3.14, "apple");
    int i;
    std::string s;

    std::tie(i, std::ignore, s) = t; // Ignore the double in the middle

    std::cout << i << " and " << s << '\n';

    return 0;
}
