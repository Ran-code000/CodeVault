<set> 是 C++ 标准库中的一个头文件，提供了 set 和 multiset 容器
这些容器用于存储有序的唯一元素 (对于 set) 和有序的非唯一元素 (对于 multiset) 

1. set 基本使用
set 是一个存储唯一元素的有序集合

#include <iostream>
#include <set>

int main() {
    // 创建一个空的 set
    set<int> s;

    // 插入元素
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(2); // 重复插入的元素不会被添加

    // 输出元素
    cout << "Set elements: ";
    for (const int &elem : s) {
        cout << elem << " ";
    }
    cout << endl;

    // 查找元素
    auto it = s.find(2);
    if (it != s.end()) {
        cout << "Element 2 found." << endl;
    } else {
        cout << "Element 2 not found." << endl;
    }

    // 删除元素
    s.erase(2);

    // 输出元素
    cout << "Set elements after erasing 2: ";
    for (const int &elem : s) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}

2. multiset 基本使用
multiset 类似于 set, 但允许存储重复元素

#include <iostream>
#include <set>

int main() {
    // 创建一个空的 multiset
    multiset<int> ms;

    // 插入元素
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(2); // 重复插入的元素会被添加

    // 输出元素
    cout << "Multiset elements: ";
    for (const int &elem : ms) {
        cout << elem << " ";
    }
    cout << endl;

    // 查找元素
    auto it = ms.find(2);
    if (it != ms.end()) {
        cout << "Element 2 found." << endl;
    } else {
        cout << "Element 2 not found." << endl;
    }

    // 删除某个元素
    ms.erase(ms.find(2)); // 删除一个 2

    // 输出元素
    cout << "Multiset elements after erasing one 2: ";
    for (const int &elem : ms) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}

3. set 其他重要功能
以下示例展示了 set 的一些其他重要功能，包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range

#include <iostream>
#include <set>

int main() {
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
    if (lb != s.end()) {
        cout << "Lower bound of 4: " << *lb << endl;
    }
    if (ub != s.end()) {
        cout << "Upper bound of 4: " << *ub << endl;
    }

    // equal_range
    auto range = s.equal_range(4);
    if (range.first != s.end()) {
        cout << "Equal range first of 4: " << *range.first << endl;
    }
    if (range.second != s.end()) {
        cout << "Equal range second of 4: " << *range.second << endl;
    }

    return 0;
}

4. multiset 其他重要功能
以下示例展示了 multiset 的一些其他重要功能，包括 size, empty, clear, count, lower_bound, upper_bound 和 equal_range。

#include <iostream>
#include <set>

int main() {
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
    if (lb != ms.end()) {
        cout << "Lower bound of 4: " << *lb << endl;
    }
    if (ub != ms.end()) {
        cout << "Upper bound of 4: " << *ub << endl;
    }

    // equal_range
    auto range = ms.equal_range(10);
    if (range.first != ms.end()) {
        cout << "Equal range first of 10: " << *range.first << endl;
    }
    if (range.second != ms.end()) {
        cout << "Equal range second of 10: " << *range.second << endl;
    }

    return 0;
}

