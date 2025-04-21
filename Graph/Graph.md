# 图

## 图的基础知识

### 图的概念

1. 顶点和边

![1](https://qcdn.itcharge.cn/images/20220307145142.png)

2. 子图
   
![1](https://qcdn.itcharge.cn/images/20220317163120.png)
    
3. 顶点的度

        （1）出度 ： 以该顶点为出发点的边的条数
        （2）入度 ： 以该顶点为终止点的边的条数
        （3）有向图中某顶点的度  ： 该顶点的出度 + 该顶点的入度
        （4）（有向 / 无向）图的度  ： 总出度 + 总入度 = 2 * 总出度 = 2 * 总入度

---

### 图的分类

---

一、有向图和无向图

![1](https://qcdn.itcharge.cn/images/20220307160017.png)

    1. 完全有向图 ： 有 n * (n - 1) / 2 条边

    2. 完全无向图 ： 有 n * (n - 1) 条弧

![1](https://qcdn.itcharge.cn/images/20220308151436.png)

---

二、有环图和无环图

![1](https://qcdn.itcharge.cn/images/20220317115641.png)

---

三、连通图和非连通图

1. 连通无向图和连通分量
![1](https://qcdn.itcharge.cn/images/20220317163249.png)

    · 连通子图：
    
        如果无向图的子图是连通无向图，则该子图称为原图的连通子图。

    · 连通分量（极⼤连通⼦图）：
    
        无向图中的一个极大连通子图（不存在包含它的更大的连通子图）称为该图的连通分量。

---

2. 强连通有向图和强连通分量
![1](https://qcdn.itcharge.cn/images/20220317133500.png)

    · 强连通子图：
    
        如果有向图的子图是连通有向图，则该子图称为原图的强连通子图

    · 连通分量（极⼤连通⼦图）：
    
        有向图中的一个极⼤强连通⼦图，称为该图的强连通分量。

---

四、带权图

![1](https://qcdn.itcharge.cn/images/20220317135207.png)

---

五、稠密图和稀疏图

    稀疏和稠密的判断条件是：
    
        E < VlogV，其中 V 表示图中边（或弧）的数量，V 表示图中顶点的数量。

---

## 图的存储结构

图的存储可以通过 ***顺序存储结构 和 链式存储结构***来实现。

顺序存储结构包括 邻接矩阵和边集数组

链式存储结构包括 邻接表、链式前向星、十字链表和邻接多重表

---

***这里只介绍邻接矩阵和邻接表***

---

### 1. 邻接矩阵

#### 概念

        邻接矩阵（Adjacency Matrix）：
        
            使用一个二维数组 matrix 来存储顶点之间的邻接关系

        （1）对于无向图：`matrix[i][j] == 1 `表示顶点 i, j 之间存在边

        （2）对于带权图：`matrix[i][j] == w `表示顶点 i, j 之间存在权重为 w 的边

---
注意：邻接矩阵适合稠密图

---
![1](https://qcdn.itcharge.cn/images/20220317144826.png)

---

#### 代码实现

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int n;                         // 图的节点数
    vector<vector<int>> adjMatrix; // 邻接矩阵
   
public:
    Graph(int n) : n(n)
    {
        adjMatrix.resize(V, vector<int>(V, 0)); // 初始化为 0
    }
    //添加边
    void addEdge(int u, int v)
    {
        adjMatrix[u][v] = 1; // 添加无向边
        adjMatrix[v][u] = 1; // 如果是无向图，需要加上反向边
    }
    // 判断边是否存在
    bool hasEdge(int u, int v)
    {
        return adjMatrix[u][v] == 1;
    }
    //打印邻接表
    void printGraph()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};


int main()
{
    Graph g(5); // 创建一个包含 5 个节点的图
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    g.printGraph(); // 打印邻接矩阵

    cout << "Edge between 0 and 1: " << g.hasEdge(0, 1) << endl;
    cout << "Edge between 2 and 4: " << g.hasEdge(2, 4) << endl;

    return 0;
}
```

---

### 2. 邻接表

#### 概念

        邻接表（Adjacency List）：

            使用顺序存储和链式存储相结合的存储结构来存储图的顶点和边。
            
            其数据结构包括两个部分，其中一个部分是数组，主要用来存放顶点的数据信息，另一个部分是链表，用来存放边信息

---
注意：邻接表适合稀疏图

---

![1](https://qcdn.itcharge.cn/images/20220317154531.png)

---
#### 代码实现

```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{
private:
    int n;                     // 图的节点数
    vector<list<int>> adjList; // 邻接表
    

public:
    Graph(int n) : n(n), adjList(n) {}

    // 添加边
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v); // 添加无向边
        adjList[v].push_back(u); // 如果是无向图，添加反向边
    }
    // 判断边是否存在
    bool hasEdge(int u, int v)
    {
        for (int neighbor : adjList[u])
            if (neighbor == v)
                return true;
        return false;
    }
    //打印邻接表
    void printGraph()
    {
        for (int i = 0; i < n; ++i)
        {
            cout << i << ": ";
            for (int neighbor : adjList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g(5); // 创建一个包含 5 个节点的图
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    g.printGraph(); // 打印邻接表

    cout << "Edge between 0 and 1: " << g.hasEdge(0, 1) << endl;
    cout << "Edge between 2 and 4: " << g.hasEdge(2, 4) << endl;

    return 0;
}
```

---

## 图的基础操作（基于邻接表）

增减节点和边

---

### 增节点

添加一个新的顶点，方法是调整邻接表的大小，并增加顶点总数numVertices

```cpp
void MyGraph::addVertex() 
{ 
    adjList.resize(numVertices++); 
} // 注意：图的顶点数量增加，但并没有与其他顶点连接的边。
```

---

### 增边

在两个顶点之间添加一条边，同时设置边的权重

```cpp

void MyGraph::addEdge(int src, int dest, int weight)
{
    // 在邻接表中，对于无向图，边需要记录在两个顶点的邻接表中。
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight});
}
```

---

### 删节点

    删除某个顶点及与其相关的所有边

    1. 清空该顶点的邻接表

    2. 从其他顶点的邻接表中删除与该顶点相关的所有边
    
    3. 最后从邻接表中删除这个顶点
   
```cpp

void MyGraph::removeVertex(int vertex)
{
  // 1. 清空该顶点的邻接表
  adjList[vertex].clear();

  // 2. 从其他顶点的邻接表中删除与该顶点相关的所有边
  for (auto &list : adjList)
  {
    /*
        remove_if 并不会真的删除元素，而是将所有不满足条件的元素移到容器的前面部分，并返回一个指向第一个被“移除”元素的迭代器。
        remove_if 只会重新排列元素，而不会改变容器的大小。要从容器中真正删除多余的元素，必须调用 erase。所以它们通常一起使用，被称为“erase-remove 习惯用法”。
    用法分解：
        remove_if(list.begin(), list.end(), condition)：将不满足条件的元素移到容器前面，返回第一个满足条件的元素的迭代器。
        list.erase(start_iterator, end_iterator)：从容器中删除从 start_iterator 到 end_iterator 之间的元素。
    */
    list.erase(remove_if(list.begin(), list.end(), [vertex](const pair<int, int> &edge)
                         { return edge.first == vertex; }),
               list.end());
  }
  
  // 3. 最后从邻接表中删除这个顶点
  adjList.erase(adjList.begin() + vertex);
  /*
    如果使用的是 std::vector 来表示邻接表（例如 std::vector<std::list<int>>），那么 adjList.erase(adjList.begin() + vertex) 是正确的。
  
    如果是 std::unordered_map 或 std::map，则需要修改为 adjList.erase(vertex)，因为这些容器允许使用键直接删除。
  */
  numVertices--;
}
```

### 删边

从两个顶点的邻接表中移除一条边（通过遍历每个顶点的邻接表，找到并移除对应的邻接关系）

```cpp

void MyGraph::removeEdge(int src, int dest)
{
  // 不严谨
  // adjList[src].remove_if([dest](pair<int, int>& edge){ return edge.first == dest;});
  // adjList[dest].remove_if([src](pair<int, int>& edge){ return edge.first == src;});
  adjList[src].erase(remove_if(adjList[src].begin(), adjList[src].end(), [dest](const pair<int, int> &edge)
                               { return edge.first == dest; }),
                     adjList[src].end());
  adjList[dest].erase(remove_if(adjList[dest].begin(), adjList[dest].end(), [src](const pair<int, int> &edge)
                                { return edge.first == src; }),
                      adjList[dest].end());
}
```

---

### 返回指定顶点的所有邻居顶点

```cpp
// 返回指定顶点的所有邻居顶点。
vector<int> MyGraph::getNeighbors(int vertex)
{
    vector<int> neighbors;
    // 通过遍历该顶点的邻接表，收集所有相邻的顶点。
    for (const auto &edge : adjList[vertex])
        neighbors.push_back(edge.first);
    return neighbors;
}
```

---
## 图的经典算法


### 一、图的遍历算法

---
    1.void DFS(int startVertex);
    2.void BFS(int startVertex);
    3.void TopologicalSort();（两种实现方式）
---

#### 1. DFS（深度优先搜索）

---

##### 算法原理

    是一种用于遍历或搜索图（包括树）中节点的算法。
    
    其基本思想是沿着一个分支尽可能深地搜索，直到该分支无法继续扩展，再回溯到上一个分支，继续探索其他可能的路径

![1](https://qcdn.itcharge.cn/images/202309042324370.png)

---

##### 算法步骤

    1. 选择一个起始节点，并访问它。
    
    2. 对每个未被访问的邻接节点，递归地应用DFS。
    
    3. 如果一个节点没有未被访问的邻接节点，则回溯到其父节点，继续进行其他分支的探索。
    
    4. 直到所有节点都被访问或图的遍历完成。

---

##### 代码实现

提要：

```txt
    function<void(int)> dfsVisit = [&](int vertex)

    1. 定义一个名为 dfsVisit 的递归 Lambda 函数，接受一个顶点作为参数。 

        function 是 C++ 标准库中的一个类模板，允许你存储可调用对象（如函数指针、lambda 表达式等）

        void(int) 指定这个函数不返回任何值（void），并且接受一个 int 类型的参数

    2.  这里存储的可调用对象 dfsVisit 是函数指针对象

        使用了 lambda 表达式 [&](int vertex) 来构造一个 function<void(int)>类模板的函数指针对象。
        
        lambda 表达式通过 [&] 以引用的方式捕获外部变量（如 visited 和 traversal）的引用，便于在递归中使用
```

```cpp
void MyGraph::DFS(int startVertex)
{
    vector<bool> visited(n, false); // 标记数组，记录顶点是否已被访问
    vector<int> traversal;       // 用于存储遍历过程中访问的顶点（路径）

    function<void(int)> dfsVisit = [&](int vertex)
    {
        // 1. 选择一个起始节点，并访问它。
        visited[vertex] = true;
        traversal.push_back(vertex);

        // 2. 对每个未被访问的邻接节点，递归地应用DFS。
        for (const auto &edge : adjList[vertex])
            if (!visited[edge.first])
                dfsVisit(edge.first);

        // 3. 如果一个节点没有未被访问的邻接节点，则回溯到其父节点，继续进行其他分支的探索。
    };
    dfsVisit(startVertex);

    for (int vertex : traversal)
        cout << vertex << " ";
    cout << endl;

}
```

---
##### 思考

---
这段代码的实现中用了 lamba 函数而没有用辅助函数，为什么？

比较 ：使用 lamba 表达式和使用辅助函数

    1. lambda 表达式

        好处在于简化代码和提高可读性

        使得递归函数 dfsVisit 可以直接在 DFS 方法内部定义，这样就能方便地捕获外部的状态（如 visited 和 traversal）而不需要额外的参数
    
    2. 辅助函数

        需要额外的参数 dfsVisit(startVertex, visited, traversal);

```cpp
//使用辅助函数版的 dfs
void MyGraph::DFS(int startVertex) 
{
    vector<bool> visited(n, false); // 标记数组
    vector<int> traversal; // 存储访问的顶点
    // 需要调用独立的递归成员函数
    dfsVisit(startVertex, visited, traversal);
    // 输出遍历顺序
    for (int vertex : traversal) 
        cout << vertex << " ";
    cout << endl;
}

void MyGraph::dfsVisit(int vertex, vector<bool>& visited, vector<int>& traversal) 
{
    visited[vertex] = true;
    traversal.push_back(vertex);
    for (const auto& edge : adjList[vertex])
        if (!visited[edge.first])
            dfsVisit(edge.first, visited, traversal); // 递归调用
}
```

---

#### 2. BFS（宽度优先搜索）

---

##### 算法原理

    是一种用于遍历或搜索图的算法
    
    它以图的一个节点为起点，首先访问该节点的所有邻接节点，然后再访问这些邻接节点的邻接节点，以此类推。简单来说，BFS 是按层次逐层展开搜索的。

---

##### 算法步骤

    1. 初始化：
        创建一个队列 q 用来存放待访问的节点。
        创建一个布尔数组 visited 用来标记节点是否被访问过。

    2. 访问节点：
        从队列中取出一个节点，标记它为已访问，并处理它（如输出）。

    3. 将该节点的所有未访问过的邻接节点加入队列中。
   
    4. 重复2 3 步，直到队列为空，表示所有可达节点都已经被访问。
##### 代码实现

```cpp
// 从给定的起始顶点进行广度优先搜索（BFS）。
void MyGraph::BFS(int startVertex)
{
    // 1. 初始化
    vector<bool> visited(n, false);
    queue<int> q;

    // 2. 访问节点
    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty())
    {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";
        // 3. 将该节点的所有未访问过的邻接节点加入队列中。
        for (const auto &edge : adjList[currentVertex])
            if (!visited[edge.first])
                visited[edge.first] = true, q.push(edge.first);
    }
    cout << endl;
}

```

---

#### 3. 拓扑排序（两种实现）

---

#### 问题引入



---

##### 算法原理

    有向无环图（DAG）

    （1）有向 ———> 按先后顺序排序（ u -> v，u 在 v 之前出现）
      
    （2）无环 ———> 需要包含所有节点

    时间复杂度 O(E + V)

---

##### 方法一：Kahn算法（基于入度）

---

***核心思想*** ： 

每次选择入度为 0 的点，然后 

删除这个点（将这个点加入结果序列中），删除它的出边（将与这个点连接的所有点入度减 1）

---

![1](https://oi-wiki.org/graph/images/topo-example.svg)

对其排序的结果就是：2 -> 8 -> 0 -> 3 -> 7 -> 1 -> 5 -> 6 -> 9 -> 4 -> 11 -> 10 -> 12

---

###### 算法步骤

    1. 计算所有节点的入度。
 
    2. 将所有入度为 0 的节点放入队列。
  
    3. 从队列中取出一个节点，并将其加入拓扑排序结果中。
   
    4. 对该节点的所有邻接节点，将其入度减 1，如果某个邻接节点的入度变为 0，则将其加入队列。

    5. 重复以上步骤，直到队列为空。
  
    6. 如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环。
   
---

###### 代码实现

---

```cpp
// 拓扑排序（Kahn 算法）

vector<int> topologicalSortKahn(int n, vector<vector<int>> &edges)
{
    vector<int> inDegree(n, 0); // 入度数组
    vector<vector<int>> adj(n); // 邻接表
    vector<int> result; //储存排序得到的数据

    // 1. 计算所有节点的入度。
    for (const auto &edge : edges)
    {
        int u = edge[0], v = edge[1];
        adj[u].push_back(v);
        inDegree[v]++;
    }

    // 2. 将所有入度为 0 的节点放入队列。
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        // 3. 从队列中取出一个节点，并将其加入拓扑排序结果中。
        int node = q.front();
        q.pop();
        result.push_back(node);

        // 4. 对该节点的所有邻接节点，将其入度减 1，如果某个邻接节点的入度变为 0，则将其加入队列。
        for (int neighbor : adj[node])
        {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    // 6. 如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环。
    if (result.size() != n)
    {
        return {}; 
    }

    return result;
}


```

---

##### 思考

为什么如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环？

    拓扑排序按 先后顺序 排序 ——> 拓扑排序中的节点数小于图中的节点数 ———> 不是所有的节点都符合排序条件 ——> 有一些节点没有先后顺序 ————> 有一些节点形成了环

---
##### 方法二：深度优先搜索（DFS）

---

***核心思想*** ： 利用递归调用栈的特点，保证入栈按倒序，正确的拓扑排序即为出栈顺序

---

###### 算法步骤

    算法步骤：

    1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
   
    2. 如果访问到某个已经在 “ 访问中 ” 状态的节点，则说明图中存在环，无法进行拓扑排序。
   
    3. DFS 完成后，标记节点为“已访问”，并将节点加入到结果栈（或者队列）中。

    4. 最终结果是栈中节点的逆序。
   
---

###### 代码实现

---

```cpp
bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited, stack<int> &result)
{
    // 当前节点正在访问，图中有环
    if (visited[node] == 1)
        return false; 
    // 当前节点已经访问过
    if (visited[node] == 2)
        return true; 

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
    visited[node] = 1; 

    for (int neighbor : adj[node])
        // 2. 如果访问到某个已经在 “ 访问中 ” 状态的节点，则说明图中存在环，无法进行拓扑排序
        if (!dfs(neighbor, adj, visited, result))
            return false;
    

    // 3. DFS 完成后，标记节点为“已访问”，并将节点加入到结果栈（或者队列）中。
    visited[node] = 2; // 标记为已访问
    result.push(node); // 将节点加入栈

    return true;
}

vector<int> topologicalSortDFS(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> adj(n);
    for (const auto &edge : edges)
        adj[edge[0]].push_back(edge[1]);

    vector<int> visited(n, 0); // 0: 未访问, 1: 正在访问, 2: 已访问
    stack<int> result;

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
    for (int i = 0; i < n; ++i)
        if (visited[i] == 0)
            if (!dfs(i, adj, visited, result))
                return {}; // 如果存在环，返回空

    vector<int> order;
    while (!result.empty())
    {
        order.push_back(result.top());
        result.pop();
    }
    return order;
}

```

---
    总结
    （1）Kahn算法（基于入度）：通常更直观易懂，适合大规模图，对于边的增删操作更加高效，且容易处理图中的环。

    （2）DFS算法：适合递归或栈的场景，能够通过递归的后序遍历得到拓扑排序，也适合用来检测环。
---
---

### 二、最短路径算法

---

#### 1. Dijkstra算法（单源最短路径）（无负权边图）

---
##### 算法原理

    1. Dijkstra 算法通过 贪心策略 计算从一个源顶点到其他所有 顶点的最短路径。

    2. 时间复杂度为 O(V^2)（未优化时）或 O((V + E) log V)（使用优先队列时）

    3. 应用：适用于无负权边的图。
   
    4. 核心思想

        (1) 选定一个点，这个点满足两个条件：a.未被选过，b.距离最短

        (2) 对于这个点的所有邻近点去尝试松弛
   
---

##### 实现代码（未优化版本）

![1](https://i-blog.csdnimg.cn/blog_migrate/79853bdb55294a2fc4f0ad34bf279da5.gif)

![1](https://i-blog.csdnimg.cn/blog_migrate/0a996bfb808b4c16f2b93019e8e5a828.png)

---
```cpp
// 求最短路径
// Dijkstra 不断选择当前距离源节点最近的未处理节点来构建最短路径。
// 贪心算法
// 时间复杂度 O(V^2)
void MyGraph::Dijkstra(int startVertex)
{
    //代表某个顶点是否被访问过，初始化所有的顶点为 false
    vector<bool> visited(n, false);
    //dis代表源点到其它点的最短距离，numeric_limits<int>::max()代表无穷
    vector<int> distances(n, numeric_limits<int>::max()); 
    //向量 prev 用来存储路径的前驱节点，用于之后路径重建，初始化为 -1
    vector<int> prev(n, -1);

    // 源点到源点的距离为 0
    distances[startVertex] = 0;

    //为什么只要寻找n-1个点呢？因为当剩下一个点的时候，这个点已经没有需要松弛的邻接点了
    for (int i = 0; i < n - 1; i++)
    {
        //进入循环之后，一开始不知道哪个是没有被访问过且距离源点最短的
        int now_minDistance = numeric_limits<int>::max();
        int now_minVertex = -1;
        
        //使用这个循环开始寻找没有被访问过且距离源点最短距离的点
        for (int j = 0; j < n; j++)
            if (!visited[j] && distances[j] < now_minDistance)
                now_minDistance = distances[j], now_minVertex = j;

        //标记当前节点已访问
        visited[now_minVertex] = true;

        //对这个距离源点最短距离的点的所有邻接点进行松弛
        for (const auto &pair : adjList[now_minVertex])
        {
            //  松弛操作（Relaxation）
            if (!visited[j] && distances[now_minVertex] + pair.second < distances[pair.first])
            {
                distances[pair.first] = distances[now_minVertex] + pair.second, prev[pair.first] = now_minVertex;
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
    
}

```

---

##### 实现代码（优化版本）

---

##### 算法原理：

    利用了优先队列（通常是最小堆）
    
    将时间复杂度降低到 O((V + E) log V)

!!! 使用 greater 来创建一个最小堆（min heap）的优先队列

!!! 使用 less 来创建一个最大堆（max heap）的优先队列

---
```cpp
void MyGraph::Dijkstra_withOptimize(int startVertex)
{
    vector<bool> visited(n, false);                       
    vector<int> distances(n, numeric_limits<int>::max()); 
    vector<int> prev(n, -1);                              


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, startVertex});
    distances[startVertex] = 0; 

    // for(int i = 0; i < n - 1; i++){
    while (!pq.empty())
    {
        // int now_minDistance = numeric_limits<int>::max();
        // int now_minVertex = -1;
        int now_minDistance = pq.top().first;
        int now_minVertex = pq.top().second;
        pq.pop();

        // for(int j = 0; j < n; j++) if(!visited[j] && distances[j] < now_minDistance) now_minDistance = distances[j], now_minVertex = j; //don't need amymore

        // !!! 如果已经访问过这个节点，跳过
        if (visited[minVertex]) 
            continue; 
            
        visited[now_minVertex] = true;

        for (const auto &neighbor : adjList[now_minVertex])
        {
            // int neighborDistance = distances[now_minVertex] + neighbor.second;
            int neighborDistance = now_minDistance + neighbor.second;

            // if(neighborDistance < distances[neighbor.first]) distances[neighbor.first] = neighborDistance, prev[neighbor.first] = now_minVertex;
            if (!visited[j] && neighborDistance < distances[neighbor.first])
            {
                distances[neighbor.first] = neighborDistance;
                prev[neighbor.first] = now_minVertex;
                pq.push({neighborDistance, neighbor.first});
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
}
```

---

#### 2. Bellman-Ford 算法（单源最短路径）（负边权图）

---

##### 算法原理

    1. Bellman-Ford 算法 ——> 带负权边的图

    2. 时间复杂度是 (O(n \times E))，其中 (n) 是顶点数，(E) 是边数。
   
    3. Bellman-Ford算法的主要思想
   
        通过最多 (n - 1) 次松弛操作（Relaxation），逐步逼近最短路径。
        
        松弛操作会不断尝试更新路径，直到无法再优化路径为止。
   
    4. 如果图中存在负权回路（负权环）的情况，这种情况是求不出最短路径的！       
   
        但 Bellman-Ford 算法可以对负权回路的情况进行检测

        负权环检测：经过 V-1 次松弛操作后，如果还存在可以松弛的边，说明图中存在负权环

---

##### 算法步骤

    1.初始化：

    dist[start] = 0，其他所有节点的距离 dist[] = ∞

    2. 松弛操作：

        对每条边 (u, v) 进行 V-1 次松弛操作。
        如果 dist[u] + weight < dist[v]，则更新 dist[v]。
    
    3.负权环检测：

        对每一条边 (u, v) 进行一次松弛操作。如果有边 (u, v) 能够进一步放松，说明图中存在负权环

        需要注意的是，以 S 点为源点跑 Bellman–Ford 算法时，如果没有给出存在负环的结果，只能说明从 S 点出发不能抵达一个负环，而不能说明图上不存在负环。

        !!!! 因此如果需要判断整个图上是否存在负环，最严谨的做法是建立一个超级源点，向图上每个节点连一条权值为 0 的边，然后以超级源点为起点执行 Bellman–Ford 算法。

---


***第一遍迭代***

第一遍起始状态

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/48c1adf5f611ed87c21329c310f72d04.png)

第一次松弛之后

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/85613e562cc7a9a7492f1bee129f0d16.png)

对 y 的相邻顶点进行松弛

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/4bd4e456457626a562a8f210c3c47242.png)

对 z 的相邻顶点进行松弛

由于z 只连出去一条边 z-> x，但是这里不会更新，因为 s->z + z->x 的距离大于目前 s->x 的距离

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/0a7b38530278e1ba906f729eb9c43af3.png)

对 t 的相邻顶点进行松弛

t连出去了两条 t->z 和 t->x ，只更新 t->z ，那之前的 s->y->z(16) 就不再是z目前的最短路径了

（当然实际写代码中的话我们的两个数组：路径距离/权值的数组 dist 和 存储路径的数组 path 就也需要相应的修改）

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/512be0fba2db90baca88eea889724006.png)

对 x 的相邻顶点进行松弛

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/f278a20ad5391e4d05884dc1206bdea3.png)

现在一趟迭代就完成了，所有顶点的相邻顶点都完成了一次松弛

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/0502bf04303d1a603ed984e186776d09.png)

***第二遍迭代***

第二遍起始状态

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/0a733fd1f527f2a78751b340262e6675.png)

第一个还是 s 顶点，但这里没有边需要更新；

然后是 y ，也没有边更新；

接着 z ，也没有更新；

再下面 t ，更新一条：现在 t 的最短路径是 2，t->z 是 -4，所以 z 的最短路径更新为 -2

！！！
我们看到这次边并没有变化，只是权值更新了；

因为上一轮z的最短路径确定为 s->t->z：2（此时t的最短路径是 s->t：6）之后，t 的最短路径又被更新成了s->y-x-t：2

t 的最短路径变了，导致 z 的最短路径也变了，但是在第二轮才更新出来

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/28b8cdfd8020e73a6df50f2faea38234.png)

最后顶点x，也没有边更新

![1](https://developer.qcloudimg.com/http-save/yehe-10926636/28b8cdfd8020e73a6df50f2faea38234.png)


##### 代码实现

```cpp


void MyGraph::BellmanFord(int startVertex)
{
    // 1.初始化
    vector<int> distances(n, numeric_limits<int>::max());
    distances[startVertex] = 0;

    // 2. 松弛操作
    // 对每条边 (u, v) 进行 V-1 次松弛操作
    for (int i = 0; i < n - 1; i++)
    {
    bool update = false;
    /*
        当然这里我们外层循环直接控制了它最多迭代 n-1 次（n为顶点个数），所有这里迭代 n-1 次就停了

        但是要注意这里的结果是不对的，因为如果我们让它继续迭代的话，有些路径是可以继续缩小的

        如果我们不控制外层循环的话，它应该就要死循环的迭代更新了
    */
    for (int j = 0; j < n; j++)
    {
        for (const auto &pair : adjList[j])
        // 如果 dist[u] + weight < dist[v]，则更新 dist[v]
        if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
        {
            distances[pair.first] = distances[j] + pair.second;
            update = true;
        }
    }

    if (update == false)
        break;
    }

    // 3.负权环检测
    // 对每一条边 (u, v) 进行一次松弛操作。
    for (int j = 0; j < n; j++)
    for (const auto &pair : adjList[j])
        // 如果有边 (u, v) 能够进一步放松，说明图中存在负权环
        if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
        {
        cout << "Graph contains a negative weight cycle!" << endl;
        return;
        }
    //打印输出
    for (int i = 0; i < n; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
    cout << endl;
}
```

---
#### 比较 Bellman-Ford 算法 和 Dijkstra 算法的工作机制

（1）关键区别：

    1. Dijkstra 算法：
       
       贪心策略
       
       每次选择尚未处理的最小距离顶点，然后对其邻接顶点进行松弛操作。
                  
       优先队列（通常是最小堆）优化

    2. Bellman-Ford 算法：
    
       动态规划算法
                    
       对图中的每条边执行 n - 1 次松弛操作来计算从源节点到其他所有节点的最短路径。
       （需要提前判断是否退出）


（2）为什么 Bellman-Ford 不需要找最小值？

        a 遍历所有边的松弛操作：
        
            Bellman-Ford 通过对所有边进行遍历和松弛操作，它保证了在最多 n-1 轮迭代后，所有的最短路径都会被正确计算出来。
            
            n-1 轮的原因是：在最坏的情况下，最短路径最多需要经过 n-1 条边。

        b 负权边的处理：

            Dijkstra 无法处理负权边，而 Bellman-Ford 可以处理负权边。
            
            由于负权边的存在，单纯选择最小值无法保证最优解，因此 Bellman-Ford 不像 Dijkstra 那样依赖每步选择最小值顶点。

---

#### 2. Floyd-Warshall算法（多源最短路径）

##### 算法原理：

    1. 动态规划
    
    2. 所有顶点对之间的最短路径。

    3. 三重循环（引入中间节点，逐步优化路径）
   
    4. 时间复杂度为 O(n^3)

    5. 适用于任何图，不管有向无向，边权正负，但是最短路必须存在。（不能有个负环）

---

##### 算法步骤   

    1. 初始化

        如果有一条边 (i, j)，则 dist[i][j] = w(i, j)，即边的权重。
        如果没有边，则 dist[i][j] = ∞。
        对于同一节点 i，初始化 dist[i][i] = 0，因为从一个节点到自身的距离为0。

    2. 迭代更新

        对于每一对节点 (i, j)，检查是否通过中间节点 k 可以得到更短的路径
        即判断是否 dist[i][j] > dist[i][k] + dist[k][j]
        如果是，则更新 dist[i][j] 为新的最短路径 dist[i][k] + dist[k][j]
    
    3. 终止条件：
   
        在经过 V 次迭代（每次迭代考虑一个新的中间节点 k）后，dist[i][j] 就是节点 i 到节点 j 的最短路径

---

![1](https://i-blog.csdnimg.cn/blog_migrate/1d82404d3cd892900c8ded3c81876eee.png)

##### 实现代码

```cpp

void MyGraph::FloydWarshall()
{
    // 1. 初始化

    // 创建一个二维向量 distances 用来存储两点之间的路径长度，初始化为顶点数量 n 大小，每个元素设置为无穷大（代表两点之间没有路径）
    vector<vector<int>> distances(n, vector<int>(n, numeric_limits<int>::max()));

    // 创建一个二维向量 prev 用来存储路径的前驱节点，用于之后路径重建，初始化为 -1
    vector<vector<int>> prev(n, vector<int>(n, -1));

    // 所有节点到自己的距离为 0，因此将 distances[i][i] 设为 0。
    for (int i = 0; i < n; i++)
        distances[i][i] = 0;

    // 初始化相邻节点之间的距离。遍历每个节点 i 的邻接表 adjList[i]，将边的权重 edge.second 设置为相应的 distances[i][edge.first]
    // 将 prev[i][edge.first] 设置为 i，表示 i 是 edge.first 的前驱。
    for (int i = 0; i < n; i++)
        for (const auto &edge : adjList[i])
            distances[i][edge.first] = edge.second, prev[i][edge.first] = i;
    
    // 2. 迭代更新
    // Floyd-Warshall 的核心！！！
    // 通过引入中间节点 k，检查从节点 i 经过 k 再到 j 的路径是否比 i 直接到 j 更短。如果是，则更新 distances[i][j] 和 prev[i][j]
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (distances[i][k] != numeric_limits<int>::max() && distances[k][j] != numeric_limits<int>::max() && distances[i][k] + distances[k][j] < distances[i][j])
                    distances[i][j] = distances[i][k] + distances[k][j], prev[i][j] = prev[k][j];
    
    // 输出所有顶点对之间的最短路径
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                cout << "Vertex " << i << " to " << j << " distance is " << distances[i][j] << endl;
}
```

---
---

### 三、最小生成树(MST)算法


---
加权无向图中，最小生成树是一个包含图中所有节点的子图

***树 ———> 包含图中所有节点***

***最小 ———> 树中的边权之和最小***

---

#### 1. Prim算法（最小生成树）

---
![1](https://i-blog.csdnimg.cn/blog_migrate/2b66edaec7381f6619a40fb03c6248fb.png)

---

##### 算法原理：

    1. 贪心算法
    
    2. 从一个起始点开始，逐步选择与当前生成树相连的、权重最小的边，直到所有节点都被包含在生成树中(贪心策略保证了每次选择的边都是当前情况下的最佳选择)
    
    3. 时间复杂度为 O(V^2)（稠密图）

    4. 应用：适用于求解加权无向图的最小生成树，尤其是稠密图（重点在加点）

---
提要 ：

    Prim算法 过程非常类似于 Dijkstra 算法

    1. distance 数组和 weight 数组保存的值的意义不同 ： 

    Dijkstra 保存从该点到起始点最短路径长度，Prim 保存已选集合和未选集合之间最短的边权

    2. Dijkstra 遍历 n - 1 轮， Prim 遍历 n 轮

---
复习 [dijkstra算法](#1-dijkstra算法单源最短路径无负权边图)

---

##### 代码实现（未优化版本）


```cpp

void MyGraph::Prim()
{
    vector<bool> visited(n, false);
    // 创建一个向量 weight，记录每个节点与生成树的最小连接权重，初始值为无穷大
    vector<int> weight(n, numeric_limits<int>::max());
    // prev 向量记录最小生成树中每个节点的父节点，初始值为 -1
    vector<int> prev(n, -1);
    // 设置起始节点的权重为 0，表示从第一个节点开始构建生成树。
    weight[0] = 0;


    for (int i = 0; i < n; i++)
    {
        int minVertex = -1;
        int minWeight = numeric_limits<int>::max();

        // 从尚未加入生成树的节点中，找到权重最小的节点 minVertex
        for (int i = 0; i < n; i++)
            if (!visited[i] && weight[i] < minWeight)
                minWeight = weight[i], minVertex = i; 

        // 如果已经访问过这个节点，跳过
        if (visited[minVertex]) 
            continue;  

        // 将该节点加入最小生成树，并增加已加入节点的计数。
        visited[minVertex] = true;

        // 遍历 minVertex 的邻接节点，更新连接权重，如果当前邻接节点的权重小于之前记录的最小权重，则更新权重并记录其父节点
        for (const auto &pair : adjList[minVertex])
            if (!visited[pair.first] && pair.second < weight[pair.first])
                weight[pair.first] = pair.second, prev[pair.first] = minVertex;

        // 打印输出
        for (int i = 1; i < n; i++)
            cout << "Edge " << prev[i] << " - " << i << " with weight " << weight[i] << endl;
    }
}
```

---

##### 代码实现（优化版本）

```cpp

void MyGraph::Prim()
{
    vector<bool> visited(n, false);                       
    vector<int> weight(n, numeric_limits<int>::max()); 
    vector<int> prev(n, -1);                              


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, startVertex});
    weight[startVertex] = 0; 

    //for (int i = 0; i < n; i++)
    while (!pq.empty())
    {
        // int minVertex = -1;
        // int minWeight = numeric_limits<int>::max();
        int now_minWeight = pq.top().first;
        int now_minVertex = pq.top().second;
        pq.pop();

        // for (int i = 0; i < n; i++)
        //     if (!visited[i] && weight[i] < minWeight)
        //         minWeight = weight[i], minVertex = i;

        // 如果已经访问过这个节点，跳过
        if (visited[minVertex]) 
            continue; 

        visited[now_minVertex] = true;


        for (const auto &neighbor : adjList[now_minVertex])
        {
            if (!visited[neighbor.first] && neighbor.second < weight[neighbor.first])
            {
                weight[neighbor.first] = neighbor.second;
                prev[neighbor.first] = now_minVertex;
                pq.push({neighborWeight, neighbor.first});
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << weight[i] << endl;
}
```
---

#### 2. Kruskal算法（最小生成树）

---

##### 算法原理：

    1. Kruskal 算法按边的权重升序排序，然后通过并查集判断边是否形成环，逐步选择不形成环的边，构建最小生成树。
   
    2. 时间复杂度为 O(E log E)

    3. 应用：适用于稀疏图的最小生成树（重点在加边）

---
   
##### 算法步骤

    1. 排序边：
   
         将所有边按照权重升序排序

    2. 初始化并查集：

        每个节点自成一个集合，即每个节点都是其自己的根

    3. 构造最小生成树：

        从排序后的边中，从最小权重开始顺序处理

    4. 对于每条边 (u, v)：

        使用并查集检查 u 和 v 是否在同一个集合中

        （1）如果不在同一个集合中，那么这条边可以安全地加入到生成树中，因为没有形成环
        （2）如果在同一个集合中，那么这条边会导致生成环，因此跳过这条边

    5. 重复步骤：直到生成树包含 V-1 条边，其中 V 是图中节点的数量

---

![1](https://i-blog.csdnimg.cn/blog_migrate/7e1964987c3db90441ee845b97f49644.gif#pic_center)

---
为了有效地检测边是否会形成环，Kruskal 算法使用 并查集（Union-Find） 数据结构

建议先去了解 [并查集](https://blog.csdn.net/2301_81373791/article/details/144189463?spm=1001.2014.3001.5502)

---

##### 代码实现

```cpp
void MyGraph::Kruskal()
{
    // 创建一个存储边的向量 edges，每个边由权重和两个顶点组成
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n; i++)
        for (const auto &edge : adjList[i])
            edges.push_back({edge.second, {i, edge.first}});

    // 1. 按边的权重升序排序：首先将图中的所有边按权重从小到大排序。
    sort(edges.begin(), edges.end());

    //2. 初始化并查集：
    // 初始化一个并查集 forest，用于判断不同的节点是否属于同一个连通分量（是否形成环）。
    // forest 保存每个顶点和其父节点
    vector<pair<int, int>> forest(n);

    // 每个节点自成一个集合，即每个节点都是其自己的根
    for (int i = 0; i < n; i++)
        forest[i] = {i, i};

    // 3. 构造最小生成树
    // 遍历所有边，如果两个节点不属于同一个集合（不形成环），则将该边加入生成树，并合并这两个集合。当加入的边数达到 (V-1) 时，最小生成树构建完成
    int numEdges = 0;
    for (const auto &edge : edges)
    {
        int root1 = find(forest, edge.second.first);
        int root2 = find(forest, edge.second.second);
        if (root1 != root2)
        {
            forest[root1] = {root1, root2};
            numEdges++;

            cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
            if (numEdges == n - 1)
                break;
        }
    }
}

// 用于并查集（Union-Find）算法中的“路径压缩”查找操作。它递归地查找某个顶点的根，并且在查找过程中把该路径上的所有顶点直接连接到根，提高后续查找效率
// 找到 vertex 所属集合的根节点
int find(vector<pair<int, int>> &forest, int vertex)
{
    // forest[vertex].second 表示顶点 vertex 的父节点。如果当前顶点的父节点不是它自己，说明它不是根节点。
    // 在递归返回后，路径压缩的核心操作发生：将 vertex 直接连接到根节点。这一步显著提高了未来查找的效率，因为路径被压缩了
    if (forest[vertex].second != vertex)
        forest[vertex].second = find(forest, forest[vertex].second);
    return forest[vertex].second;
    /*假设
    forest = {
        {0, 0},  // 顶点 0 的父节点是 0 （根节点）
        {1, 0},  // 顶点 1 的父节点是 0
        {2, 1},  // 顶点 2 的父节点是 1
        {3, 2},  // 顶点 3 的父节点是 2
        {4, 3},  // 顶点 4 的父节点是 3
    }
    这个结构表示顶点 0 是根节点，其他顶点通过不同的路径连接到根节点 0。


    调用 find(forest, 4) 来查找顶点 4 的根节点

    forest[4].second != 4：顶点 4 的父节点是 3，而不是它自己，所以继续递归查找

    递归调用 find(forest, 3)：

    forest[3].second != 3：顶点 3 的父节点是 2，继续递归查找

    递归调用 find(forest, 2)：

    forest[2].second != 2：顶点 2 的父节点是 1，继续递归查找

    递归调用 find(forest, 1)：

    forest[1].second != 1：顶点 1 的父节点是 0，继续递归查找

    递归调用 find(forest, 0)：

    forest[0].second == 0：顶点 0 的父节点是它自己，返回 0 作为根节点


    接着路径压缩开始生效：
    路径压缩应该是从递归返回时，按递归调用的顺序依次更新父节点。
    forest[1].second = 0（顶点 1 的父节点更新为根节点 0）
    forest[2].second = 0（顶点 2 的父节点更新为根节点 0）
    forest[3].second = 0（顶点 3 的父节点更新为根节点 0）
    forest[4].second = 0（顶点 4 的父节点更新为根节点 0）

    最终，find(forest, 4) 返回 0，并且路径压缩后，forest 变为：
    forest = {
        {0, 0},  // 顶点 0 的父节点是 0
        {1, 0},  // 顶点 1 的父节点是 0
        {2, 0},  // 顶点 2 的父节点是 0
        {3, 0},  // 顶点 3 的父节点是 0
        {4, 0},  // 顶点 4 的父节点是 0
    }
    */
}
```

---

### 总结

每种算法适用的图类型：

    1. Dijkstra、Floyd-Warshall、Prim：适用于非负权图。

    2. Bellman-Ford：适用于含有负权边的图。

    3. Kruskal、Prim：适用于无向图（生成树问题）。

    4. 拓扑排序：适用于有向无环图（DAG）
   
时间复杂度总结：

    1. Dijkstra：O(n^2)（未优化） / O((n + E) log n)（优化版）

    2. Bellman-Ford：O(n \times E)

    3. Floyd-Warshall：O(n ^ 3)

    4. Prim：O(n ^ 2)

    5. Kruskal：O(E log E)

    6. 拓扑排序：O(n + E)

---

## 完整代码

```cpp

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <functional>
#include <chrono>
#include <stack>
// #include "Timer.h"
using namespace std;
class MyGraph
{
    int VertexNum;                        // 顶点数量
    vector<list<pair<int, int>>> adjList; // 邻接表来储存图，每个顶点的邻接表是一个存储了与该顶点相邻的顶点及其权重的列表

    // 用于并查集（Union-Find）算法中的“路径压缩”查找操作。它递归地查找某个顶点的根，并且在查找过程中把该路径上的所有顶点直接连接到根，提高后续查找效率
    // 找到 vertex 所属集合的根节点
    int find(vector<pair<int, int>> &forest, int vertex)
    {
        // forest[vertex].second 表示顶点 vertex 的父节点。如果当前顶点的父节点不是它自己，说明它不是根节点。
        // 在递归返回后，路径压缩的核心操作发生：将 vertex 直接连接到根节点。这一步显著提高了未来查找的效率，因为路径被压缩了
        if (forest[vertex].second != vertex)
            forest[vertex].second = find(forest, forest[vertex].second);
        return forest[vertex].second;
        /*假设
        forest = {
            {0, 0},  // 顶点 0 的父节点是 0 （根节点）
            {1, 0},  // 顶点 1 的父节点是 0
            {2, 1},  // 顶点 2 的父节点是 1
            {3, 2},  // 顶点 3 的父节点是 2
            {4, 3},  // 顶点 4 的父节点是 3
        }
        这个结构表示顶点 0 是根节点，其他顶点通过不同的路径连接到根节点 0。

        调用 find(forest, 4) 来查找顶点 4 的根节点。
        forest[4].second != 4：顶点 4 的父节点是 3，而不是它自己，所以继续递归查找。
        递归调用 find(forest, 3)：
        forest[3].second != 3：顶点 3 的父节点是 2，继续递归查找。
        递归调用 find(forest, 2)：
        forest[2].second != 2：顶点 2 的父节点是 1，继续递归查找。
        递归调用 find(forest, 1)：
        forest[1].second != 1：顶点 1 的父节点是 0，继续递归查找。
        递归调用 find(forest, 0)：
        forest[0].second == 0：顶点 0 的父节点是它自己，返回 0 作为根节点。

        接着路径压缩开始生效：
        路径压缩应该是从递归返回时，按递归调用的顺序依次更新父节点。
        forest[1].second = 0（顶点 1 的父节点更新为根节点 0）
        forest[2].second = 0（顶点 2 的父节点更新为根节点 0）
        forest[3].second = 0（顶点 3 的父节点更新为根节点 0）
        forest[4].second = 0（顶点 4 的父节点更新为根节点 0）

        最终，find(forest, 4) 返回 0，并且路径压缩后，forest 变为：
        forest = {
            {0, 0},  // 顶点 0 的父节点是 0
            {1, 0},  // 顶点 1 的父节点是 0
            {2, 0},  // 顶点 2 的父节点是 0
            {3, 0},  // 顶点 3 的父节点是 0
            {4, 0},  // 顶点 4 的父节点是 0
        }

        */
    }

public:
    MyGraph(int vertices) : VertexNum(vertices), adjList(vertices) {} // 初始化图，指定顶点数量，并为每个顶点创建空的邻接表。
    void addVertex();
    void addEdge(int src, int dest, int weight = 1);
    void removeVertex(int vertex);
    void removeEdge(int src, int dest);
    vector<int> getNeighbors(int vertex);
    // 遍历
    void DFS(int startVertex);
    void BFS(int startVertex);
    // 用于有向无环图
    void TopologicalSort();
    void topologicalSortKahn();
    void topologicalSortDfs();
    // 最短路径
    void Dijkstra(int startVertex);
    void Dijkstra_withOptimize(int startVertex); // Optimizze by priority_queue
    void FloydWarshall();
    void BellmanFord(int startVertex);
    void BellmanFord_withOptimize(int startVertex);
    // 最小生成树
    void Prim();
    void Kruskal();

    void TarjanSCC();
    void CriticalPath();

    void printGraph()
    {
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << "Vertex " << i << ": ";
            for (auto const &neighbor : adjList[i])
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            cout << endl;
        }
    }
    void drawGraph()
    {
        cout << "\nGraph Structure:\n";
        cout << "    (1)\n";
        cout << "     / \\\n";
        cout << " 10 /   \\ 15\n";
        cout << "   /     \\\n";
        cout << "(0)---5---(3)\n";
        cout << "   \\     /\n";
        cout << "  6 \\   / 4\n";
        cout << "     \\ /\n";
        cout << "    (2)\n";
    }
};

// 添加一个新的顶点，方法是调整邻接表的大小，并增加顶点总数VertexNum
void MyGraph::addVertex()
{
    adjList.resize(VertexNum++);
} // 注意：图的顶点数量增加，但并没有与其他顶点连接的边。

// 在两个顶点之间添加一条边，同时设置边的权重
void MyGraph::addEdge(int src, int dest, int weight)
{
    // 在邻接表中，对于无向图，边需要记录在两个顶点的邻接表中。
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight});
}

// 删除某个顶点及与其相关的所有边（清空该顶点的邻接列表，并从其他顶点的邻接列表中移除所有与该顶点相关的边）
// ！！！！！
// 1. remove_if 标记删除：首先将所有与要删除的顶点相关的边标记为删除。
// 2. erase 真正删除：然后使用 erase 来删除 remove_if 标记的元素。
// 3. 删除顶点：最后，将整个顶点及其邻接表从 adjList 中移除
void MyGraph::removeVertex(int vertex)
{
    // 清空该顶点的邻接表
    adjList[vertex].clear();
    // 从其他顶点的邻接表中删除与该顶点相关的所有边
    for (auto &list : adjList)
    {
        // remove_if 并不会真的删除元素，而是将所有不满足条件的元素移到容器的前面部分，并返回一个指向第一个被“移除”元素的迭代器。
        // remove_if 只会重新排列元素，而不会改变容器的大小。要从容器中真正删除多余的元素，必须调用 erase。所以它们通常一起使用，被称为“erase-remove 习惯用法”。
        // 用法分解：
        // remove_if(list.begin(), list.end(), condition)：将不满足条件的元素移到容器前面，返回第一个满足条件的元素的迭代器。
        // list.erase(start_iterator, end_iterator)：从容器中删除从 start_iterator 到 end_iterator 之间的元素。
        list.erase(remove_if(list.begin(), list.end(), [vertex](const pair<int, int> &edge)
                             { return edge.first == vertex; }),
                   list.end());
    }
    // 最后从邻接表中删除这个顶点
    adjList.erase(adjList.begin() + vertex);
    VertexNum--;
}

// 从两个顶点的邻接表中移除一条边（通过遍历每个顶点的邻接表，找到并移除对应的邻接关系）
void MyGraph::removeEdge(int src, int dest)
{
    // 不严谨
    // adjList[src].remove_if([dest](pair<int, int>& edge){ return edge.first == dest;});
    // adjList[dest].remove_if([src](pair<int, int>& edge){ return edge.first == src;});
    adjList[src].erase(remove_if(adjList[src].begin(), adjList[src].end(), [dest](const pair<int, int> &edge)
                                 { return edge.first == dest; }),
                       adjList[src].end());
    adjList[dest].erase(remove_if(adjList[dest].begin(), adjList[dest].end(), [src](const pair<int, int> &edge)
                                  { return edge.first == src; }),
                        adjList[dest].end());
}

// 返回指定顶点的所有邻居顶点。
vector<int> MyGraph::getNeighbors(int vertex)
{
    vector<int> neighbors;
    // 通过遍历该顶点的邻接表，收集所有相邻的顶点。
    for (const auto &edge : adjList[vertex])
        neighbors.push_back(edge.first);
    return neighbors;
}

// 遍历

// 从给定的起始顶点进行深度优先搜索（DFS）
void MyGraph::DFS(int startVertex)
{
    vector<bool> visited(VertexNum, false); // 标记数组，记录顶点是否已被访问
    vector<int> traversal;                  // 用于存储遍历过程中访问的顶点（路径）

    // 定义一个名为dfsVisit的递归Lambda函数，接受一个顶点作为参数。
    // function 是 C++ 标准库中的一个类模板，允许你存储可调用对象（如函数指针、lambda 表达式等）。void(int) 指定这个函数不返回任何值（void），并且接受一个 int 类型的参数
    // 这里存储的可调用对象 dfsVisit 是函数指针对象

    //[&](int vertex) 是 lambda 表达式
    // 使用了 lambda 表达式来构造一个 function<void(int)>类模板的函数指针对象。这个对象可以接受一个整数参数并且不返回值，lambda 表达式通过 [&] 捕获外部变量（如 visited 和 traversal）的引用，便于在递归中使用
    //& 会捕获外部作用域中的所有变量，以引用的方式（在这个例子中是 visited 和 traversal）。这种捕获方式便于在递归调用中保持状态
    function<void(int)> dfsVisit = [&](int vertex)
    {
        visited[vertex] = true;
        traversal.push_back(vertex);
        for (const auto &edge : adjList[vertex])
            if (!visited[edge.first])
                dfsVisit(edge.first);
    };
    dfsVisit(startVertex);
    for (int vertex : traversal)
        cout << vertex << " ";
    cout << endl;
    /*
    使用 lambda 表达式的主要好处在于简化代码和提高可读性。
    使得递归函数 dfsVisit 可以直接在 DFS 方法内部定义，这样就能方便地捕获外部的状态（如 visited 和 traversal）而不需要额外的参数
    否则：
    void MyGraph::DFS(int startVertex) {
        vector<bool> visited(VertexNum, false); // 标记数组
        vector<int> traversal; // 存储访问的顶点
        // 需要调用独立的递归成员函数
        dfsVisit(startVertex, visited, traversal);
        // 输出遍历顺序
        for (int vertex : traversal) cout << vertex << " ";
        cout << endl;
    }
    void MyGraph::dfsVisit(int vertex, vector<bool>& visited, vector<int>& traversal) {
        visited[vertex] = true;
        traversal.push_back(vertex);
        for (const auto& edge : adjList[vertex])
            if (!visited[edge.first])
                dfsVisit(edge.first, visited, traversal); // 递归调用
    }
    */
}
// 从给定的起始顶点进行广度优先搜索（BFS）。
void MyGraph::BFS(int startVertex)
{
    vector<bool> visited(VertexNum, false);
    queue<int> queue;
    // 起始顶点标记入队
    visited[startVertex] = true;
    queue.push(startVertex);
    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();
        cout << currentVertex << " ";
        // 遍历当前顶点的邻接表，找到未被访问过的压入队列
        for (const auto &edge : adjList[currentVertex])
            if (!visited[edge.first])
                visited[edge.first] = true, queue.push(edge.first);
    }
    cout << endl;
}
// 拓扑排序
void MyGraph::TopologicalSort()
{
    vector<bool> visited(VertexNum, false); // 记录每个顶点是否访问过
    stack<int> topoStack;                   // 存储拓扑排序结果的栈

    // 使用 Lambda 函数实现的递归 DFS
    function<void(int)> topologicalDFS = [&](int vertex)
    {
        visited[vertex] = true;
        for (const auto &pair : adjList[vertex])
            if (!visited[pair.first])
                topologicalDFS(pair.first);
        // 将该顶点加入栈，表示它的所有邻居已经处理完毕
        topoStack.push(vertex);
    };
    // 对图中的每个顶点进行 DFS，确保所有连通分量都被遍历
    for (int i = 0; i < VertexNum; i++)
        if (!visited[i])
            topologicalDFS(i);
    cout << "Topological Sort: ";
    while (!topoStack.empty())
        cout << topoStack.top() << " ", topoStack.pop();
    cout << endl;
}
void MyGraph::topologicalSortKahn()
{
    vector<int> inDegree(VertexNum, 0); // 入度数组
    vector<int> result;                 // 储存排序得到的数据

    // 1. 计算所有节点的入度。
    for (int i = 0; i < VertexNum; i++)
        for (const auto &pair : adjList[i])
            inDegree[pair.first]++;

    // 2. 将所有入度为 0 的节点放入队列。
    queue<int> q;
    for (int i = 0; i < VertexNum; i++)
        if (inDegree[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        // 3. 从队列中取出一个节点，并将其加入拓扑排序结果中。
        int node = q.front();
        q.pop();
        result.push_back(node);

        // 4. 对该节点的所有邻接节点，将其入度减 1，如果某个邻接节点的入度变为 0，则将其加入队列。
        for (auto &pair : adjList[node])
        {
            inDegree[pair.first]--;
            if (inDegree[pair.first] == 0)
                q.push(pair.first);
        }
    }

    // 6. 如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环。
    if (result.size() != VertexNum)
    {
        cout << "has cycle\n";
    }
    else
    {
        for (int node : result)
            cout << node << " ";
    }
}

bool dfs(int node, vector<list<pair<int, int>>> &adj, vector<int> &visited, stack<int> &result)
{
    // 当前节点正在访问，图中有环
    if (visited[node] == 1)
        return false;
    // 当前节点已经访问过
    if (visited[node] == 2)
        return true;

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
    visited[node] = 1;

    for (auto &neighbor : adj[node])
        // 2. 如果访问到某个已经在 “ 访问中 ” 状态的节点，则说明图中存在环，无法进行拓扑排序
        if (!dfs(neighbor.first, adj, visited, result))
            return false;

    // 3. DFS 完成后，标记节点为“已访问”，并将节点加入到结果栈（或者队列）中。
    visited[node] = 2; // 标记为已访问
    result.push(node); // 将节点加入栈

    return true;
}

void MyGraph::topologicalSortDfs()
{
    vector<int> visited(VertexNum, 0); // 0: 未访问, 1: 正在访问, 2: 已访问
    stack<int> result;

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
    for (int i = 0; i < VertexNum; ++i)
    {
        if (visited[i] == 0)
        {
            if (!dfs(i, adjList, visited, result))
            {
                cout << "has cycle\n";
                return;
            }
        }
    }

    vector<int> order;
    while (!result.empty())
    {
        order.push_back(result.top());
        result.pop();
    }

    for (int node : order)
        cout << node << " ";
}

// 求最短路径
// Dijkstra 算法通过 贪心策略 计算从一个源顶点到其他所有 顶点的最短路径。
// 时间复杂度为 O(V^2)（未优化时）或 O((V + E) log V)（使用优先队列时）
// 应用：适用于无负权边的图。
// 核心思想
//     (1) 选定一个点，这个点满足两个条件：a.未被选过，b.距离最短
//     (2) 对于这个点的所有邻近点去尝试松弛
void MyGraph::Dijkstra(int startVertex)
{
    vector<bool> visited(VertexNum, false);
    vector<int> distances(VertexNum, numeric_limits<int>::max()); // the maximum possible integer value
    vector<int> prev(VertexNum, -1);

    distances[startVertex] = 0;
    for (int i = 0; i < VertexNum - 1; i++)
    {
        int now_minDistance = numeric_limits<int>::max();
        int now_minVertex = -1;

        for (int j = 0; j < VertexNum; j++)
            if (!visited[j] && distances[j] < now_minDistance)
                now_minDistance = distances[j], now_minVertex = j;

        visited[now_minVertex] = true;

        for (const auto &pair : adjList[now_minVertex])
        {
            // Relaxation （松弛操作）
            if (!visited[pair.first] && distances[now_minVertex] + pair.second < distances[pair.first])
                distances[pair.first] = distances[now_minVertex] + pair.second, prev[pair.first] = now_minVertex;
        }
    }
    for (int i = 0; i < VertexNum; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
}

// 利用了优先队列（通常是最小堆）
// 将时间复杂度降低到 O((V + E) log V)。
void MyGraph::Dijkstra_withOptimize(int startVertex)
{
    vector<bool> visited(VertexNum, false);
    vector<int> distances(VertexNum, numeric_limits<int>::max());
    vector<int> prev(VertexNum, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // distances[startVertex] = 0;
    pq.push({0, startVertex});
    distances[startVertex] = 0; // distance to start vertex is 0

    // for(int i = 0; i < VertexNum - 1; i++){
    while (!pq.empty())
    {
        // int now_minDistance = numeric_limits<int>::max();
        // int now_minVertex = -1;
        int now_minDistance = pq.top().first;
        int now_minVertex = pq.top().second;
        pq.pop();

        // for(int j = 0; j < VertexNum; j++) if(!visited[j] && distances[j] < now_minDistance) now_minDistance = distances[j], now_minVertex = j; //don't need amymore

        // visited[now_minVertex] = true;
        visited[now_minVertex] = true;

        for (const auto &neighbor : adjList[now_minVertex])
        {
            // int neighborDistance = distances[now_minVertex] + neighbor.second;
            int neighborDistance = now_minDistance + neighbor.second;

            // if(neighborDistance < distances[neighbor.first]) distances[neighbor.first] = neighborDistance, prev[neighbor.first] = now_minVertex;
            if (!visited[neighbor.first] && neighborDistance < distances[neighbor.first])
                distances[neighbor.first] = neighborDistance, prev[neighbor.first] = now_minVertex, pq.push({neighborDistance, neighbor.first});
        }
    }
    for (int i = 0; i < VertexNum; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
}
// Floyd-Warshall 是找到任意两点之间的最短路径
// Floyd-Warshall 是一种动态规划算法，用于求解任意两点之间的最短路径
// 时间复杂度为 (O(V^3))，其中 (V) 是顶点数量。这个算法的原理是通过引入中间节点，逐步优化路径
void MyGraph::FloydWarshall()
{
    // 创建一个二维向量 distances 用来存储两点之间的路径长度，初始化为顶点数量 VertexNum 大小，每个元素设置为无穷大（代表两点之间没有路径）
    vector<vector<int>> distances(VertexNum, vector<int>(VertexNum, numeric_limits<int>::max()));
    // 创建一个二维向量 prev 用来存储路径的前驱节点，用于之后路径重建，初始化为 -1
    vector<vector<int>> prev(VertexNum, vector<int>(VertexNum, -1));
    // 所有节点到自己的距离为 0，因此将 distances[i][i] 设为 0。
    for (int i = 0; i < VertexNum; i++)
        distances[i][i] = 0;
    // 初始化相邻节点之间的距离。遍历每个节点 i 的邻接表 adjList[i]，将边的权重 edge.second 设置为相应的 distances[i][edge.first]，并将 prev[i][edge.first] 设置为 i，表示 i 是 edge.first 的前驱。
    for (int i = 0; i < VertexNum; i++)
        for (const auto &edge : adjList[i])
            distances[i][edge.first] = edge.second, prev[i][edge.first] = i;
    // Floyd-Warshall 的核心！！！
    // 通过引入中间节点 k，检查从节点 i 经过 k 再到 j 的路径是否比 i 直接到 j 更短。如果是，则更新 distances[i][j] 和 prev[i][j]
    for (int k = 0; k < VertexNum; k++)
        for (int i = 0; i < VertexNum; i++)
            for (int j = 0; j < VertexNum; j++)
                if (distances[i][k] != numeric_limits<int>::max() && distances[k][j] != numeric_limits<int>::max() && distances[i][k] + distances[k][j] < distances[i][j])
                    distances[i][j] = distances[i][k] + distances[k][j], prev[i][j] = prev[k][j];
    // 输出所有顶点对之间的最短路径
    for (int i = 0; i < VertexNum; i++)
        for (int j = 0; j < VertexNum; j++)
            if (i != j)
                cout << "Vertex " << i << " to " << j << " distance is " << distances[i][j] << endl;
}
// Bellman-Ford Algorithm
// Bellman-Ford算法用于在 带负权边的图中计算单源最短路径，即从给定起点到其他所有顶点的最短距离。
// 与Dijkstra算法不同，Bellman-Ford能够处理图中存在负权重边的情况。它的时间复杂度是 (O(V \times E))，其中 (V) 是顶点数，(E) 是边数。
// Bellman-Ford算法的主要思想是通过松弛操作（Relaxation），逐步逼近最短路径。松弛操作会不断尝试更新路径，直到无法再优化路径为止。
// Bellman-Ford执行最多 (V-1) 次松弛操作，其中 (V) 是图的顶点数。最后通过一次额外的检查判断是否存在 负权重环（negative weight cycle）。
void MyGraph::BellmanFord(int startVertex)
{
    vector<int> distances(VertexNum, numeric_limits<int>::max());
    distances[startVertex] = 0;

    for (int i = 0; i < VertexNum - 1; i++)
        for (int j = 0; j < VertexNum; j++)
            for (const auto &pair : adjList[j])
                // Relaxation 操作(n - 1)times
                if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
                    distances[pair.first] = distances[j] + pair.second;
    // Check for negative weight cycles
    for (int j = 0; j < VertexNum; j++)
        for (const auto &pair : adjList[j])
            // Relaxation 操作 1 times
            if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
            {
                cout << "Graph contains a negative weight cycle!" << endl;
                return;
            }
    for (int i = 0; i < VertexNum; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
    cout << endl;
    /*
    Bellman-Ford 算法，它和 Dijkstra 算法的工作机制有所不同。

    关键区别：
    Dijkstra 算法：基于贪心策略，每次选择尚未处理的最小距离顶点（即在某一步找到最短路径的那个顶点），然后对其邻接顶点进行松弛操作。
                   因此，Dijkstra 需要通过优先队列（通常是最小堆）来不断找到当前未处理的最小距离顶点。

    Bellman-Ford 算法：是一种动态规划算法，不依赖贪心策略，因此不需要像 Dijkstra 一样在每一步都寻找最小值。
                    它通过对图中的每条边执行 n - 1 次松弛操作来计算从源节点到其他所有节点的最短路径。松弛操作的次数保证了最短路径的计算。
    为什么 Bellman-Ford 不需要找最小值？
    遍历所有边的松弛操作：Bellman-Ford 通过对所有边进行遍历和松弛操作，它保证了在最多 n-1 轮迭代后，所有的最短路径都会被正确计算出来。
    n-1 轮的原因是：在最坏的情况下，最短路径最多需要经过 n-1 条边。

    负权边的处理：Dijkstra 无法处理负权边，而 Bellman-Ford 可以处理负权边。
    由于负权边的存在，单纯选择最小值无法保证最优解，因此 Bellman-Ford 不像 Dijkstra 那样依赖每步选择最小值顶点。
    */
}
// 优化 Bellman-Ford Algorithm
void MyGraph::BellmanFord_withOptimize(int startVertex)
{
    vector<int> distances(VertexNum, numeric_limits<int>::max());
    distances[startVertex] = 0;

    for (int i = 0; i < VertexNum - 1; i++)
    {
        bool update = false;
        for (int j = 0; j < VertexNum; j++)
        {
            for (const auto &pair : adjList[j])
            {
                if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
                {
                    distances[pair.first] = distances[j] + pair.second;
                    update = true;
                }
            }
        }
        if (update == false)
            break;
    }

    for (int j = 0; j < VertexNum; j++)
        for (const auto &pair : adjList[j])
            // Relaxation 操作 1 times
            if (distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first])
            {
                cout << "Graph contains a negative weight cycle!" << endl;
                return;
            }
    for (int i = 0; i < VertexNum; i++)
        if (i != startVertex)
            cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
    cout << endl;
}

// 最小生成树

// 从一个起始点开始，逐步选择与当前生成树相连的、权重最小的边，直到所有节点都被包含。其时间复杂度是 (O(V^2))，适用于稠密图
// 过程非常类似于 Dijkstra 算法
//(只有 distance 数组和 weight 数组保存的值的意义不同 ： Dijkstra 保存从该点到起始点最短路径长度，Prim 保存已选集合和未选集合之间最短的边权)
void MyGraph::Prim()
{
    vector<bool> visited(VertexNum, false);
    // 创建一个向量 weight，记录每个节点与生成树的最小连接权重，初始值为无穷大
    vector<int> weight(VertexNum, numeric_limits<int>::max());
    // prev 向量记录最小生成树中每个节点的父节点，初始值为 -1
    vector<int> prev(VertexNum, -1);
    // 设置起始节点的权重为 0，表示从第一个节点开始构建生成树。
    weight[0] = 0;
    for (int i = 0; i < VertexNum; i++)
    {
        int minWeight = numeric_limits<int>::max();
        int minVertex = -1;
        // 从尚未加入生成树的节点中，找到权重最小的节点 minVertex
        for (int i = 0; i < VertexNum; i++)
            if (!visited[i] && weight[i] < minWeight)
                minWeight = weight[i], minVertex = i;
        // 将该节点加入最小生成树，并增加已加入节点的计数。
        visited[minVertex] = true;
        // 遍历 minVertex 的邻接节点，更新连接权重，如果当前邻接节点的权重小于之前记录的最小权重，则更新权重并记录其父节点
        for (const auto &pair : adjList[minVertex])
            if (!visited[pair.first] && pair.second < weight[pair.first])
                weight[pair.first] = pair.second, prev[pair.first] = minVertex;

        for (int i = 1; i < VertexNum; i++)
            cout << "Edge " << prev[i] << " - " << i << " with weight " << weight[i] << endl;
    }
}
// 按照边的权重进行排序，每次选择权重最小的边，只要不形成环。
// 时间复杂度是 (O(E \log E))，适用于稀疏图
void MyGraph::Kruskal()
{
    // 创建一个存储边的向量 edges，每个边由权重和两个顶点组成
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < VertexNum; i++)
        for (const auto &edge : adjList[i])
            edges.push_back({edge.second, {i, edge.first}});
    // 按照边的权重升序排序。
    sort(edges.begin(), edges.end());
    // 初始化一个并查集 forest，用于判断不同的节点是否属于同一个连通分量（是否形成环）。
    // forest 保存每个顶点和其父节点
    vector<pair<int, int>> forest(VertexNum);
    for (int i = 0; i < VertexNum; i++)
        forest[i] = {i, i};
    // 遍历所有边，如果两个节点不属于同一个集合（不形成环），则将该边加入生成树，并合并这两个集合。当加入的边数达到 (V-1) 时，最小生成树构建完成
    int numEdges = 0;
    for (const auto &edge : edges)
    {
        int root1 = find(forest, edge.second.first);
        int root2 = find(forest, edge.second.second);
        if (root1 != root2)
        {
            forest[root1] = {root1, root2};
            numEdges++;
            cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
            if (numEdges == VertexNum - 1)
                break;
        }
    }
    // 错误写法
    // 没有输出的原因是因为条件 if(root1 != root2) 不成立，因为此时所有边都已连接，形成了一个最小生成树（MST），没有剩余边可以输出。
    //  for(const auto& edge : edges){
    //      int root1 = find(forest, edge.second.first);
    //      int root2 = find(forest, edge.second.second);
    //      if(root1 != root2) cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
    //  }
}

// Tarjan's Algorithm for finding SCCs
// Tarjan 算法是一种用于找出有向图中的强连通分量（SCC）的算法。
// 其基本原理是通过深度优先搜索（DFS）来遍历图，并使用两个数组来跟踪节点的发现时间和最低可达节点，从而识别出强连通分量。
void MyGraph::TarjanSCC()
{
    // disc记录每个节点被访问的时间戳，low记录当前节点可追溯到的最小时间戳
    vector<int> disc(VertexNum, -1), low(VertexNum, -1);
    // 存储当前访问的节点
    stack<int> stk;
    // 用于标记节点是否在栈中，防止重复入栈。
    vector<bool> visited(VertexNum, false);
    // 初始化一个时间计数器time，用于跟踪访问节点的顺序
    int time = 0;

    // 定义一个递归函数SCCDFS，接受一个整数参数u，表示当前访问的节点。
    // 使用function和lambda表达式来实现递归。
    function<void(int)> SCCDFS = [&](int vertex)
    {
        // 访问节点 vertex ，同时更新 disc 和 low 数组为当前时间戳 time
        disc[vertex] = low[vertex] = ++time;
        // 将节点 vertex 压入栈中，表示它是当前路径的一部分
        stk.push(vertex);
        // 将节点 vertex 标记为在栈中
        visited[vertex] = true;

        // 遍历邻接列表 adjList 中与节点 vertex 相连的每个邻接节点。
        for (const auto &pair : adjList[vertex])
        {
            // 如果节点 pair.first 尚未被访问（即disc[pair.first]为-1），则递归访问它
            // 更新low[vertex]，检查 vertex 的 low 值是否需要更新为邻接节点 pair.first 的 low 值
            if (disc[pair.first] == -1)
                SCCDFS(pair.first), low[vertex] = min(low[vertex], low[pair.first]);
            // 如果节点 vertex 已在栈中，则表示 vertex 是当前 SCC 的一部分。
            // 更新low[vertex]，以便记录到达 pair.first 的时间戳
            else if (visited[pair.first])
                low[vertex] = min(low[vertex], disc[pair.first]);
        }

        // If vertex is the head node of an SCC
        // 如果当前节点 vertex 的 low 值等于其 disc 值，则 vertex 是当前强连通分量的根节点。
        if (low[vertex] == disc[vertex])
        {
            // 输出标记，表示即将打印一个强连通分量
            cout << "SCC: ";
            // 开始一个循环，直到栈顶元素为 vertex
            while (stk.top() != vertex)
            {
                cout << stk.top() << " ";
                // 将节点v标记为不在栈中并从栈中弹出
                visited[vertex] = false;
                stk.pop();
            }
            // 打印根节点 vertex ，完成当前强连通分量的输出
            cout << vertex << endl;
            // 将节点v标记为不在栈中并从栈中弹出
            visited[vertex] = false;
            stk.pop();
        }
    };
    // 如果节点i尚未被访问，则调用SCCDFS
    for (int i = 0; i < VertexNum; i++)
        if (disc[i] == -1)
            SCCDFS(i);
}
// Critical Path Method (CPM)
// Critical Path Method (CPM) 是一种用于项目管理的技术，它帮助确定项目中所有任务的最早完成时间以及最关键的任务路径（即关键路径）。
// 关键路径是决定项目最早完成时间的任务序列，如果这些任务中的任何一个延迟，项目的整体完成时间也会延迟。
// 从起点到终点的正向计算，确定每个任务的最早开始和最早完成时间；
// 通过从终点到起点的逆向计算，确定任务的最晚开始时间。
void MyGraph::CriticalPath()
{
    vector<int> topoOrder;
    vector<int> earliestStart(VertexNum, 0), latestStart(VertexNum, numeric_limits<int>::max());

    // Topological sort to find the order of vertices
    vector<bool> visited(VertexNum, false);
    function<void(int)> topologicalDFS = [&](int vertex)
    {
        visited[vertex] = true;
        for (const auto &pair : adjList[vertex])
            if (!visited[pair.first])
                topologicalDFS(pair.first);
        topoOrder.push_back(vertex);
    };

    for (int i = 0; i < VertexNum; i++)
        if (!visited[i])
            topologicalDFS(i);

    reverse(topoOrder.begin(), topoOrder.end());

    // Forward pass to calculate earliest start times
    for (auto it = topoOrder.begin(); it != topoOrder.end(); it++)
        for (const auto &pair : adjList[*it])
            earliestStart[pair.first] = max(earliestStart[pair.first], earliestStart[*it] + pair.second);

    latestStart[topoOrder[0]] = earliestStart[topoOrder[0]];

    // Backward pass to calculate latest start times
    for (auto it = topoOrder.rbegin(); it != topoOrder.rend(); it++)
        for (const auto &pair : adjList[*it])
            latestStart[*it] = min(latestStart[*it], latestStart[pair.first] - pair.second);

    cout << "Critical Path: ";
    for (int vertex : topoOrder)
        for (const auto &pair : adjList[vertex])
            if (earliestStart[vertex] == latestStart[pair.first] - pair.second)
                cout << vertex << " -> " << pair.first << " (weight " << pair.second << "), ";
    cout << endl;
}
// text function
int main()
{
    MyGraph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.printGraph();
    g.drawGraph();
    // 遍历
    cout << "DFS:\n";
    g.DFS(0);
    cout << endl;

    cout << "BFS:\n";
    g.BFS(0);
    cout << endl;

    // cout << "Topological Sort:\n";
    // g.TopologicalSort();
    // cout << endl;

    // cout << "topologicalSortKahn:\n";
    // g.topologicalSortKahn();
    // cout << endl;

    // cout << "topologicalSortDfs:\n";
    // g.topologicalSortDfs();
    // cout << endl;

    // 最短路径
    cout << "Dijkstra:\n";
    g.Dijkstra(0);
    cout << endl;

    cout << "Dijkstra_with_optimize:\n";
    g.Dijkstra_withOptimize(0);
    cout << endl;

    cout << "Floyd_Warshall:\n";
    g.FloydWarshall();
    cout << endl;

    cout << "Bellman_Ford from Vertex 0:\n";
    g.BellmanFord(0);
    cout << endl;

    cout << "BellmanFord_withOptimize from Vertex 0:\n";
    g.BellmanFord_withOptimize(0);
    cout << endl;

    // 最小生成树
    cout << "Prim:\n";
    g.Prim();
    cout << endl;

    cout << "Kruskal:\n";
    g.Kruskal();
    cout << endl;

    // 强连通分量
    cout << "Finding SCCs using Tarjan's Algorithm:\n";
    g.TarjanSCC();
    cout << endl;

    // 关键路径
    cout << "Critical Path Method:\n";
    g.CriticalPath();
    cout << endl;

    // Timer::measureTime("Dijkstra", &MyGraph::Dijkstra, &g, 0);
    // Timer::measureTime("Dijkstra_with_optimize", &MyGraph::Dijkstra_withOptimize, &g, 0);
    // Timer::measureTime("FloydWarshall", &MyGraph::FloydWarshall, &g);
    // Timer::measureTime("Prim", &MyGraph::Prim, &g);
    // Timer::measureTime("Kruskal", &MyGraph::Kruskal, &g);
    // Timer::measureTime("TopologicalSort", &MyGraph::topologicalSortKahn, &g);
    // Timer::measureTime("TopologicalSort", &MyGraph::topologicalSortDfs, &g);
    // Timer::measureTime("BellmanFord", &MyGraph::BellmanFord, &g, 0);
    // Timer::measureTime("TarjanSCC", &MyGraph::TarjanSCC, &g);
    // Timer::measureTime("CriticalPath", &MyGraph::CriticalPath, &g);
    return 0;
}
```
