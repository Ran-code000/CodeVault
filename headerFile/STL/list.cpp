C++ 标准库中的 list 是一个双向链表容器, 它允许高效地在容器中的任何位置插入和删除元素
允许在容器的两端快速插入和删除元素， 代价是放弃随机访问功能

1. 包含头文件
#include <iostream>
#include <list>
所有 list 的使用都需要包含 <list> 头文件

2. 创建 list

list<int> lst; // 创建一个空的 list
list<int> lst2(5, 10); // 创建一个包含 5 个值为 10 的元素的 list

3. 基本操作
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

4. 示例代码
#include <iostream>
#include <list>

int main() {
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
    for (int value : lst) {
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
    for (int value : lst) {
        cout << value << " "; // 输出: 10 20
    }
    cout << endl;

    // 清空列表
    lst.clear();
    cout << "List size after clear: " << lst.size() << endl; // 输出 0

    return 0;
}

5. 其他操作
splice: 将一个列表的元素移动到另一个列表中
remove: 移除所有等于指定值的元素
remove_if: 按条件移除元素
unique: 移除连续重复的元素
sort: 对列表进行排序
merge: 合并两个已排序的列表
reverse: 反转列表中的元素

6. 示例代码
#include <iostream>
#include <list>

bool isOdd(int n) {
    return n % 2 != 0;
}

int main() {
    list<int> lst1 = {1, 2, 3, 4, 5};
    list<int> lst2 = {10, 20, 30};
    
    // splice: 将 lst2 的内容移动到 lst1 的第二个位置
    auto it = lst1.begin();
    ++it; // 移动到第二个位置
    lst1.splice(it, lst2);

    // lst1 现在包含: 1 10 20 30 2 3 4 5
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 1 10 20 30 2 3 4 5

    // remove: 移除所有等于 2 的元素
    lst1.remove(2);

    // lst1 现在包含: 1 10 20 30 3 4 5
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 1 10 20 30 3 4 5

    // remove_if: 按条件移除元素，移除所有奇数
    lst1.remove_if(isOdd);

    // lst1 现在包含: 10 20 30 4
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 10 20 30 4

    // unique: 移除连续重复的元素
    lst1.push_back(4);
    lst1.unique();

    // lst1 现在包含: 10 20 30 4
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 10 20 30 4

    // sort: 对列表进行排序
    lst1.sort();

    // lst1 现在包含: 4 10 20 30
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 4 10 20 30

    // merge: 合并两个已排序的列表
    list<int> lst3 = {5, 15, 25};
    lst1.merge(lst3);

    // lst1 现在包含: 4 5 10 15 20 25 30
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 4 5 10 15 20 25 30

    // reverse: 反转列表
    lst1.reverse();

    // lst1 现在包含: 30 25 20 15 10 5 4
    for (int value : lst1) {
        cout << value << " ";
    }
    cout << endl; // 输出: 30 25 20 15 10 5 4

    return 0;
}

应用
#include <list>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;
int main() {
    list<int> lst = {1, 2, 3, 4, 5};
    vector<int> vec = {10, 20, 30, 40, 50};

    //text1-----------------------------------------------------------------------
    copy(vec.begin(), vec.end(), front_inserter(lst));
    // 使用 front_inserter 将 vec 的元素复制到 lst 的前面
    // 注意 1st 是 list 不是 vector, 因此可以用 front_inserter
    for (int val : lst) {
        cout << val << " ";
    }
    cout << "\n";
    //输出50 40 30 20 10 1 2 3 4 5 （逆序）


    //text2-----------------------------------------------------------------------
    auto it1 = lst.begin(); // 找到插入点
    copy(vec.begin(), vec.end(), inserter(lst, it1));

    for (int val : lst) {
        cout << val << " ";
    }
    cout << "\n";
    //输出10 20 30 40 50 50 40 30 20 10 1 2 3 4 5 （正序）


    //text3-----------------------------------------------------------------------
    auto it = next(lst.begin(), 5); // 找到插入点
    copy(vec.begin(), vec.end(), inserter(lst, it));
    // 使用 inserter 将 vec 的元素复制到 lst 的中间 


    for (int val : lst) {
        cout << val << " ";
    }
    cout << "\n";
    //输出10 20 30 40 50 10 20 30 40 50 50 40 30 20 10 1 2 3 4 5 （正序）


    return 0;
}
