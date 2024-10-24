C++ 标准库中的 deque （双端队列）是一个序列容器
允许在容器的两端快速插入和删除元素， 支持随机访问功能

1. 包含头文件
#include <iostream>
#include <deque>
所有 deque 的使用都需要包含 <deque> 头文件

2. 创建 deque
deque<int> dq; // 创建一个空的 deque
deque<int> dq2(5, 10); // 创建一个包含 5 个值为 10 的元素的 deque
deque<int> dq3 = {1, 2, 3, 4, 5}; // 使用初始化列表

3. 基本操作
push_back: 在末尾添加元素
push_front: 在头部添加元素
pop_back: 移除末尾元素
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

4. 示例代码
#include <iostream>
#include <deque>

int main() {
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
    for (int value : dq) {
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
    for (int value : dq) {
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

5. 其他操作
resize: 改变容器大小
shrink_to_fit: 减少容量以适应大小
assign: 重新填充容器
swap: 交换两个容器的内容
emplace, emplace_back, emplace_front: 原地构造元素

6. 示例代码
#include <iostream>
#include <deque>

int main() {
    deque<int> dq = {1, 2, 3, 4, 5};

    // resize: 改变容器大小
    dq.resize(3);
    for (int value : dq) {
        cout << value << " "; // 输出: 1 2 3
    }
    cout << endl;

    dq.resize(5, 10);
    for (int value : dq) {
        cout << value << " "; // 输出: 1 2 3 10 10
    }
    cout << endl;

    // shrink_to_fit: 减少容量
    dq.shrink_to_fit();

    // assign: 重新填充容器
    dq.assign(4, 7);
    for (int value : dq) {
        cout << value << " "; // 输出: 7 7 7 7
    }
    cout << endl;

    // swap: 交换两个容器的内容
    deque<int> dq2 = {100, 200};
    dq.swap(dq2);
    for (int value : dq) {
        cout << value << " "; // 输出: 100 200
    }
    cout << endl;

    for (int value : dq2) {
        cout << value << " "; // 输出: 7 7 7 7
    }
    cout << endl;

    // emplace, emplace_back, emplace_front: 原地构造元素
    dq.emplace_back(300); // 在末尾原地构造 300
    dq.emplace_front(50); // 在头部原地构造 50
    dq.emplace(dq.begin() + 1, 75); // 在第二个位置原地构造 75

    // 现在 dq 包含: 50 75 100 200 300
    for (int value : dq) {
        cout << value << " "; // 输出: 50 75 100 200 300
    }
    cout << endl;

    return 0;
}
总结
deque 提供了丰富的操作接口，可以高效地在容器的两端插入和删除元素，同时也支持随机访问元素。