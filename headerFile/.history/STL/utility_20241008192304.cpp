<utility> 头文件在 C++ 标准库中提供了一系列实用程序组件，包括配对对象、交换操作、移动语义以及辅助功能。
以下是 <utility> 中定义的一些主要组件及其用法：

1. pair:
pair 是一个结构，它可以存储两个可能不同类型的值。这在需要将两个值视为一个单元时非常有用。

#include <utility>
#include <iostream>
#include <string>

int main() 
{
    pair<int, string> p = {1, "apple"};

    cout << "The pair is: (" << p.first << ", " << p.second << ")\n";

    return 0;
}


2. make_pair:
make_pair 是一个辅助函数，用于创建 pair 对象，其类型由传递给它的参数推断出来。

#include <utility>
#include <iostream>

int main() 
{
    auto p = make_pair(42, "hello");

    cout << "The pair contains: " << p.first << " and " << p.second << "\n";

    return 0;
}


#include <vector>
#include <utility> // for pair
#include <iostream>

int main() 
{
    vector<pair<int, char>> vec = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

    // Adding a new pair
    vec.push_back(make_pair(4, 'd'));

    // Iterating over the vector and printing its content
    for (const auto& p : vec) 
    {
        cout << p.first << ": " << p.second << '\n';
    }
}


3. move:
move 将其参数转换为右值引用，允许移动语义而不是复制。

#include <utility>
#include <vector>
#include <iostream>

int main() 
{
    vector<int> src = {1, 2, 3};
    vector<int> dest = move(src); // Moves the contents of src to dest

    cout << "src size after move: " << src.size() << '\n'; // src is now empty
    cout << "dest has " << dest.size() << " elements.\n";

    return 0;
}


4. swap:
swap 交换两个对象的值。

#include <utility>
#include <iostream>

int main() 
{
    int a = 5, b = 10;
    swap(a, b);

    cout << "a is " << a << ", b is " << b << "\n";

    return 0;
}


5. forward:
forward 用于实现完美转发，它可以保持对象的左值或右值属性。

#include <utility>
#include <iostream>

void overloaded(int &arg) 
{ 
    cout << "by lvalue\n"; 
}

void overloaded(int &&arg) 
{ 
    cout << "by rvalue\n"; 
}

template <typename T>
void forwarding(T &&arg) 
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


6. declval:
declval 用于在不构造对象的情况下获得对象类型的引用，主要用于模板元编程和类型推导。

#include <utility>
#include <type_traits>

template <typename T>
void foo(const T &) 
{
    static_assert(is_same<decltype(declval<T>()), T&&>::value, "T must be deducible to T&&");
}


7. tie:
tie 可以创建一个 tuple 的引用包装器，这常用于解构 pair 或 tuple。

#include <utility>
#include <tuple>
#include <iostream>

int main() 
{
    pair<int, string> p = make_pair(2, "pear");
    int num;
    string fruit;

    tie(num, fruit) = p; // Unpack the pair into two variables

    cout << num << " " << fruit << '\n';

    return 0;
}


8. ignore:
ignore 是一个特殊的对象，用以忽略 tie 的某个位置。

#include <utility>
#include <tuple>
#include <iostream>

int main()  
{
    tuple<int, double, string> t = make_tuple(1, 3.14, "apple");
    int i;
    string s;

    tie(i, ignore, s) = t; // Ignore the double in the middle

    cout << i << " and " << s << '\n';

    return 0;
}
