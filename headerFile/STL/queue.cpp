C++ 标准库中的 queue 是一种容器适配器, 它提供了一个先进先出(FIFO)的数据结构
queue 一般使用 deque 或 list 作为底层容器, 但也可以使用其他支持双端操作的容器

1. 包含头文件
#include <iostream>
#include <queue>
所有 queue 的使用都需要包含 <queue> 头文件

2. 创建 queue
默认情况下, queue 使用 deque 作为底层容器

queue<int> q; // 默认使用 deque 作为底层容器
也可以显式指定底层容器

queue<int, list<int>> q2; // 使用 list 作为底层容器

3. 基本操作
push: 向队列尾部添加元素
pop: 移除队列头部元素
front: 访问队列头部元素
back: 访问队列尾部元素
empty: 检查队列是否为空
size: 获取队列中的元素数量
下面是一个综合示例，展示了以上所有操作：

#include <iostream>
#include <queue>

int main() {
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
    if (q.empty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Queue is not empty" << endl; // 输出 Queue is not empty
    }

    return 0;
}

4. 使用自定义底层容器
示例展示了如何使用 list 作为底层容器：

#include <iostream>
#include <queue>
#include <list>

int main() {
    queue<int, list<int>> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.front() << endl; // 输出 10
    cout << "Back element: " << q.back() << endl; // 输出 30

    return 0;
}

5. 遍历队列
queue 不提供直接的迭代器访问，因此遍历队列需要使用 pop 操作来逐个访问元素。注意, pop 操作会移除元素

#include <iostream>
#include <queue>

int main() {
    queue<int> q;

    // 向队列添加元素
    q.push(10);
    q.push(20);
    q.push(30);

    // 遍历队列
    while (!q.empty()) {
        cout << q.front() << " "; // 输出元素
        q.pop(); // 移除元素
    }
    cout << endl; // 输出: 10 20 30

    return 0;
}

6. 使用优先级队列(priority_queue)
priority_queue 是一种特殊的队列, 其中最大（默认）或最小元素（可通过比较器自定义）总是位于队列的顶部

包含头文件：
#include <queue>
基本用法：

#include <iostream>
#include <queue>
#include <vector>

int main() {
    priority_queue<int> pq; // 默认最大优先级队列

    // 添加元素
    pq.push(30);
    pq.push(10);
    pq.push(20);

    // 访问并移除元素
    while (!pq.empty()) {
        cout << pq.top() << " "; // 输出最大元素
        pq.pop(); // 移除最大元素
    }
    cout << endl; // 输出: 30 20 10

    return 0;
}

自定义比较器以创建最小优先级队列：

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for greater<int>

int main() {
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




C++ 标准库中的 priority_queue 是一个容器适配器，提供了优先队列的功能。
优先队列是一种数据结构，其中每个元素都有一个优先级，元素根据优先级顺序进行出队操作。
默认情况下，priority_queue 是一个最大堆（即优先级最高的元素先出队），但你也可以自定义比较函数来实现最小堆。

1. 包含头文件
#include <iostream>
#include <queue>
#include <vector>
#include <functional> // greater
所有 priority_queue 的使用都需要包含 <queue> 头文件。

2. 创建 priority_queue
priority_queue<int> pq1; // 默认使用 vector 作为底层容器，最大堆
priority_queue<int, vector<int>, greater<int>> pq2; // 最小堆

3. 基本操作
push: 向优先队列添加元素
pop: 移除优先队列的顶部元素
top: 访问优先队列的顶部元素
empty: 检查优先队列是否为空
size: 获取优先队列中的元素数量

4. 示例代码
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main() {
    // 创建一个默认的优先队列（最大堆）
    priority_queue<int> pq;

    // 向优先队列添加元素
    pq.push(10);
    pq.push(20);
    pq.push(5);

    // 访问并移除优先队列的顶部元素
    cout << "Top element: " << pq.top() << endl; // 输出 20
    pq.pop();

    cout << "Top element after pop: " << pq.top() << endl; // 输出 10

    // 优先队列的大小
    cout << "Priority queue size: " << pq.size() << endl; // 输出 2

    // 检查优先队列是否为空
    if (pq.empty()) {
        cout << "Priority queue is empty" << endl;
    } else {
        cout << "Priority queue is not empty" << endl; // 输出 Priority queue is not empty
    }

    return 0;
}

5. 使用自定义比较器
你可以通过传递自定义的比较器来创建其他类型的优先队列，例如最小堆：

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main() {
    // 创建一个最小堆
    priority_queue<int, vector<int>, greater<int>> min_heap;

    // 向最小堆添加元素
    min_heap.push(10);
    min_heap.push(20);
    min_heap.push(5);

    // 访问并移除最小堆的顶部元素
    cout << "Top element: " << min_heap.top() << endl; // 输出 5
    min_heap.pop();

    cout << "Top element after pop: " << min_heap.top() << endl; // 输出 10

    return 0;
}
6. 使用自定义数据类型和比较器
可以使用自定义数据类型和比较器。例如，假设有一个任务调度系统，其中任务有不同的优先级。

#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Task {
    int priority;
    string description;

    // 自定义比较器，用于最大堆
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

int main() {
    priority_queue<Task> task_queue;

    // 向任务队列添加任务
    task_queue.push({1, "Low priority task"});
    task_queue.push({3, "High priority task"});
    task_queue.push({2, "Medium priority task"});

    // 访问并移除优先级最高的任务
    while (!task_queue.empty()) {
        Task top_task = task_queue.top();
        cout << "Task: " << top_task.description << " with priority " << top_task.priority << endl;
        task_queue.pop();
    }

    return 0;
}

7. 使用 priority_queue 解决实际问题
合并 K 个排序链表
#include <iostream>
#include <queue>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct compare {
    bool operator()(const ListNode* l1, const ListNode* l2) {
        return l1->val > l2->val; // 最小堆
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, compare> pq;

    // 初始化优先队列
    for (ListNode* list : lists) {
        if (list) pq.push(list);
    }

    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (!pq.empty()) {
        ListNode* top = pq.top(); //pq.top() 获取优先队列中值最小的节点（也就是当前最小的头节点）
        pq.pop();
        curr->next = top;
        curr = curr->next;
        if (top->next) pq.push(top->next); //检查当前节点 top 的后继节点是否存在(针对待合并的一条链表)
    }

    return dummy.next;
}

int main() {
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
    while (curr) {
        cout << curr->val << " ";
        curr = curr->next;
    }

    // 释放内存
    while (merged_list) {
        ListNode* temp = merged_list;
        merged_list = merged_list->next;
        delete temp;
    }

    return 0;
}
