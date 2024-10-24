排序回调函数
通常是指用来指定排序准则的函数或函数对象，它告诉排序算法如何比较两个元素的大小。
这种机制允许开发者自定义排序的行为，而不仅仅是依赖于元素的默认比较操作（如使用 < 操作符）。

作用
在排序中，回调函数用于决定两个元素之间的顺序。标准库中的排序函数，
如 std::sort,通常接受一个可选的第三参数——比较函数。
这个比较函数应当能够接受两个待比较的元素作为参数，并返回一个布尔值，指示第一个参数是否在排序中应该位于第二个参数之前。

示例代码
1. 通过一个结构体数组进行演示，这个结构体包含两个字段，并以其中一个字段为排序准则：

#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

// 比较函数，按年龄排序
bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age; // 升序排序
}

int main() {
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // 使用自定义比较函数进行排序
    std::sort(people.begin(), people.end(), compareByAge);//注意这里第三个参数是函数名 ———— compareByAge

    // 输出排序后的结果
    for (const auto& person : people) {
        std::cout << person.name << " is " << person.age << " years old.\n";
    }

    return 0;
}
在这个例子中，我们定义了一个 Person 结构体，并用 std::vector 来存储多个 Person 实例。
我们定义了一个名为 compareByAge 的函数，该函数接收两个 Person 对象，并根据它们的年龄返回一个布尔值。
我们通过传递这个函数给 std::sort，来按照人物的年龄进行排序。

2. 使用函数对象(Functor)
除了使用普通函数作为回调之外，还可以使用对象来实现相同的功能。
这些对象可以重载 operator()，从而表现得像函数一样。这种方法的优势是它可以保持状态

#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

// 函数对象
struct CompareByAge {
    bool operator()(const Person& a, const Person& b) const {
        return a.age < b.age;
    }
};

int main() {
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}zhe
    };

    // 使用函数对象进行排序
    std::sort(people.begin(), people.end(), CompareByAge());//注意这里第三个参数是函数名 ———— compareByAge()

    // 输出排序后的结果
    for (const auto& person : people) {
        std::cout << person.name << " is " << person.age << " years old.\n";
    }

    return 0;
}
在这个示例中，我们定义了一个名为 CompareByAge 的结构体，该结构体重载了 operator() 方法。
这使得 CompareByAge 的实例可以像函数一样被调用，以此实现排序的自定义规则。


优先队列
优先队列通常是通过堆(Heap)数据结构实现的。堆是一种特殊的完全二叉树，其每个节点的值都满足堆属性，
即对于最大堆，父节点的值大于或等于其子节点的值；对于最小堆，则父节点的值小于或等于其子节点的值。

优先队列实现
C++ 标准库中通过模板类 std::priority_queue 提供了优先队列的实现。
这个模板类定义在 <queue> 头文件中。默认情况下, std::priority_queue 实现了一个最大堆。

1. 如何使用 std::priority_queue

#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> pq;

    // 插入元素
    pq.push(10);
    pq.push(5);
    pq.push(20);

    // 循环直到优先队列为空
    while (!pq.empty()) {
        // 输出最顶元素
        std::cout << pq.top() << std::endl;
        // 弹出最顶元素
        pq.pop();
    }

    return 0;
}
2. 自定义比较器
要实现最小堆，可以通过提供自定义比较器来改变排序准则：

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // std::greater

int main() {
    // 使用 greater 比较函数实现最小堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);

    while (!minHeap.empty()) {
        std::cout << minHeap.top() << std::endl;
        minHeap.pop();
    }

    return 0;
}

优化方案
在高级用法和优化中，优先队列可以与其他数据结构如哈希表结合使用，以支持更复杂的操作如删除任意元素、减小关键字等。
例如，斐波那契堆和配对堆支持这些操作，但在标准库中未直接提供。

算法竞赛中的应用例题
在算法竞赛中，优先队列经常用于处理如 Dijkstra 算法、Huffman 编码等问题。下面是一个使用优先队列的 Dijkstra 算法实现：

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

// 顶点，边的结构
struct Edge {
    int to, cost;
};

// 用于优先队列的比较
struct Node {
    int v, distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

void dijkstra(int source, const std::vector<std::vector<Edge>>& graph, std::vector<int>& dist) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({source, 0});
    dist[source] = 0;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int u = node.v;

        if (dist[u] < node.distance) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int cost = edge.cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({v, dist[v]});
            }
        }
    }
}

int main() {
    int n = 5; // Number of nodes
    std::vector<std::vector<Edge>> graph(n);
    std::vector<int> dist(n, INF);

    // 构建图
    graph[0] = {{1, 2}, {3, 6}};
    graph[1] = {{2, 3}, {3, 8}, {4, 5}};
    graph[2] = {{4, 7}};
    graph[3] = {{4, 9}};
    // Dijkstra 算法
    dijkstra(0, graph, dist);

    // 输出最短路径结果
    for (int i = 0; i < n; ++i) {
        std::cout << "Shortest distance to node " << i << " is " << dist[i] << std::endl;
    }

    return 0;
}
在这个例子中用优先队列来维护当前待处理的节点，确保每次都能快速获取具有最小距离的节点，从而有效地实现 Dijkstra 算法。
这种实现可以显著提高算法的效率，特别是在处理大规模图时。

