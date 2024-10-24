C++ 标准库中的 <iterator> 头文件定义了许多用于迭代器操作的工具和类型
以下是 <iterator> 头文件中一些常见的类和函数, 以及它们的用法和示例代码

1. iterator_traits
iterator_traits 是一个模板类，用于提取迭代器的属性类型 (如 value_type, difference_type, pointer, reference 和 iterator_category)

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    using Iterator = vector<int>::iterator;
    iterator_traits<Iterator>::value_type x = 5; // x 是 int 类型
    cout << "Value type: " << typeid(x).name() << endl;
    return 0;
}

2. distance
distance 用于计算两个迭代器之间的距离
distance() 可以用于任何类型的迭代器，包括输入迭代器和前向迭代器，而直接相减仅适用于随机访问迭代器

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    auto distance = distance(vec.begin(), vec.end());
    cout << "Distance: " << distance << endl; // 输出 5
    return 0;
}

3. advance
advance 用于将迭代器前进特定的距离

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin();
    advance(it, 3);
    cout << "Iterator advanced to: " << *it << endl; // 输出 4
    return 0;
}

4. next 和 prev
next 和 prev 分别用于获取迭代器前进或后退指定距离后的新迭代器
next() 和 prev() 返回一个新的迭代器，而不修改原始迭代器
直接对迭代器进行加减操作会修改原始迭代器

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = next(vec.begin(), 3);
    cout << "Next iterator points to: " << *it << endl; // 输出 4

    it = prev(vec.end(), 2);
    cout << "Prev iterator points to: " << *it << endl; // 输出 4
    return 0;
}

5. back_inserter, front_inserter 和 inserter
这些函数返回插入迭代器, 它们用于在容器的特定位置插入元素

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

int main() {
    vector<int> vec = {1, 2, 3};
    list<int> lst;

    // back_inserter
    copy(vec.begin(), vec.end(), back_inserter(lst));
    for (int n : lst) cout << n << " "; // 输出 1 2 3
    cout << endl;

    // front_inserter
    copy(vec.begin(), vec.end(), front_inserter(lst));
    for (int n : lst) cout << n << " "; // 输出 3 2 1 1 2 3
    cout << endl;

    // inserter
    auto it = lst.begin();
    advance(it, 3);
    copy(vec.begin(), vec.end(), inserter(lst, it));
    for (int n : lst) cout << n << " "; // 输出 3 2 1 1 2 3 1 2 3
    cout << endl;

    return 0;
}
back_inserter() 是一个简便的工厂函数, 用于创建 back_insert_iterator
back_inserter(vec2) 创建了一个 back_insert_iterator<vector<int>>, 它们在功能上是等价的
(同理 front_inserter(v) 和 front_insert_iterator<vector<int>>(v))
(同理 insert_iterator(v, it) 和 insert_iterator<vector<int>>(v, it))

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
int main() {
    vector<int> vec = {1, 2, 3};
    vector<int> v;
    list<int> l;

    // back_insert_iterator<vector<int>> (v)
    copy(vec.begin(), vec.end(), back_insert_iterator<vector<int>>(v));
    cout << "v:\n";
    for (int n : v) cout << n << " "; // 输出 1 2 3
    cout << endl;

    // insert_iterator<vector<int>>(v, v.begin())
    copy(vec.begin(), vec.end(), insert_iterator<vector<int>>(v, v.begin()));
    cout << "v:\n";
    for (int n : v) cout << n << " "; // 输出 1 2 3 1 2 3
    cout << endl;

    // front_insert_iterator<vector<int>>(v)
    copy(vec.begin(), vec.end(), front_insert_iterator<list<int>>(l));
    cout << "l:\n";
    for (int n : l) cout << n << " "; // 输出 3 2 1
    cout << endl;

    return 0;
}

6. ostream_iterator 和 istream_iterator
用于从输出流和输入流进行迭代

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // ostream_iterator
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl; // 输出 1 2 3 4 5

    // istream_iterator
    vector<int> vec2;
    cout << "Enter numbers (non-number to end): ";
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec2));

    cout << "You entered: ";
    copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}

7. reverse_iterator
用于反向迭代

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    reverse_iterator<vector<int>::iterator> rit = vec.rbegin();
    for (; rit != vec.rend(); ++rit) {
        cout << *rit << " "; // 输出 5 4 3 2 1
    }
    cout << endl;
    return 0;
}

8. move_iterator
用于将普通迭代器转换为移动迭代器

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
    vector<string> vec = {"one", "two", "three"};
    vector<string> vec2;

    // move_iterator
    move(vec.begin(), vec.end(), back_inserter(vec2));
    for (const auto& str : vec2) {
        cout << str << " "; // 输出 one two three
    }
    cout << endl;

    return 0;
}
