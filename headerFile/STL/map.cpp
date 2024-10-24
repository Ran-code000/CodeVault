<map> 是 C++ 标准库中的一个头文件，提供了 map 和 multimap 容器, 这些容器用于存储键值对，并按键自动排序

1. map 基本使用
map 是一个存储有序键值对的容器，每个键都是唯一的

#include <iostream>
#include <map>

int main() {
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
    for (const auto &pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 查找元素
    auto it = m.find(3);
    if (it != m.end()) {
        cout << "Element with key 3 found: " << it->second << endl;
    } else {
        cout << "Element with key 3 not found." << endl;
    }

    // 删除元素
    m.erase(2);

    // 输出元素
    cout << "Map elements after erasing key 2:" << endl;
    for (const auto &pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}

2. multimap 基本使用
multimap 类似于 map, 但允许存储重复的键

#include <iostream>
#include <map>

int main() {
    // 创建一个空的 multimap
    multimap<int, string> mm;

    // 插入元素
    mm.insert({1, "one"});
    mm.insert({2, "two"});
    mm.insert({3, "three"});
    mm.insert({2, "TWO"}); // 重复键

    // 输出元素
    cout << "Multimap elements:" << endl;
    for (const auto &pair : mm) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 查找元素
    auto range = mm.equal_range(2);
    cout << "Elements with key 2:" << endl;
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // 删除某个键的所有元素
    mm.erase(2);

    // 输出元素
    cout << "Multimap elements after erasing key 2:" << endl;
    for (const auto &pair : mm) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}

3. map 其他重要功能
以下示例展示了 map 的一些其他重要功能，包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range 

#include <iostream>
#include <map>

int main() {
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
    if (lb != m.end()) {
        cout << "Lower bound of key 4: " << lb->first << ": " << lb->second << endl;
    }
    if (ub != m.end()) {
        cout << "Upper bound of key 4: " << ub->first << ": " << ub->second << endl;
    }

    // equal_range
    auto range = m.equal_range(4);
    if (range.first != m.end()) {
        cout << "Equal range first of key 4: " << range.first->first << ": " << range.first->second << endl;
    }
    if (range.second != m.end()) {
        cout << "Equal range second of key 4: " << range.second->first << ": " << range.second->second << endl;
    }

    return 0;
}

4. multimap 其他重要功能
以下示例展示了 multimap 的一些其他重要功能，包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range

#include <iostream>
#include <map>

int main() {
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
    if (lb != mm.end()) {
        cout << "Lower bound of key 4: " << lb->first << ": " << lb->second << endl;
    }
    if (ub != mm.end()) {
        cout << "Upper bound of key 4: " << ub->first << ": " << ub->second << endl;
    }

    // equal_range
    auto range = mm.equal_range(4);
    if (range.first != mm.end()) {
        cout << "Equal range first of key 4: " << range.first->first << ": " << range.first->second << endl;
    }
    if (range.second != mm.end()) {
        cout << "Equal range second of key 4: " << range.second->first << ": " << range.second->second << endl;
    }

    return 0;
}
