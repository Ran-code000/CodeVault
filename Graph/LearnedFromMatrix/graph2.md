# 判断有向图内是否有环（2 种方法）

思考过程：

    有向图 ——> 有方向 ——> 有方向就有顺序 ——> 节点分先后 ——> 可排序

    有环 ——> 某节点可以经过某个路径到达自己 ——> 节点不存在先后 ——> 不可排序

**有向图内是否有环问题 ——> 针对有向图的是否可排序问题 ——> 拓扑排序问题**


拓扑排序针对有向无环图（DAG）

**针对无环显然就能够判断是否有环**


## 法一： 拓扑排序（Kahn 算法）

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

### 思考

为什么如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环？

    拓扑排序按 先后顺序 排序 ——> 拓扑排序中的节点数小于图中的节点数 ———> 不是所有的节点都符合排序条件 ——> 有一些节点没有先后顺序 ————> 有一些节点形成了环

---

## 方法二：深度优先搜索（DFS）

---

***核心思想*** ： 利用递归调用栈的特点，保证入栈按倒序，正确的拓扑排序即为出栈顺序

---

### 算法步骤

    算法步骤：

    1. 对每个未被访问的节点执行 DFS，标记该节点为访问中。
   
    2. 如果访问到某个已经在 “ 访问中 ” 状态的节点，则说明图中存在环，无法进行拓扑排序。
   
    3. DFS 完成后，标记节点为“已访问”，并将节点加入到结果栈（或者队列）中。

    4. 最终结果是栈中节点的逆序。
   
---

### 代码实现

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

## 例题

### 题目描述

```txt
判断有向图内是否有环

题目描述

给定一个有向图，判断其中是否存在环，有的话输出has circle，没有输出no circle 

请完成函数void Graphcircle(GraphList *g); 

输入包含3个部分
第一个部分为第一行两个数k和m表示顶点数和边数
第二部分为第二行有k个数为顶点的值（与编号相同）
第三部分为后面m行，每行为vi vj w分别表示从节点i到节点j的边权值为5 
输出为一行，有环或无环

样例输入
8 9
0 1 2 3 4 5 6 7
0 1 1
1 5 1
0 2 1
2 3 1
3 4 1
4 5 1
4 6 1
7 3 1
​
样例输出
has circle
​
样例输入
5 6
0 1 2 3 4
1 0 9
1 2 3
2 0 2
2 3 5
3 4 1
0 4 6
​
输出
no circle
​

```

### 关键代码实现

```cpp
#include "circle.h"
#include <vector>
#include <iostream>
using namespace std;

bool dfs(int node, vector<int>& visited, GraphList* & g) {
    if (visited[node] == 1) {
        return true;  // 找到环
    }
    if (visited[node] == 2) {
        return false;  // 已经处理过的节点，无环
    }

    visited[node] = 1;  // 标记当前节点正在访问中

    if(g->adjList[node].firstedge != nullptr){
        EdgeNode* curr = g->adjList[node].firstedge;
        while(curr){
            if(dfs(curr->adjvex, visited, g)){
                return true;
            }
            curr = curr->next;
        }
    }

    visited[node] = 2;  // 标记节点访问完毕
    return false;
}

void Graphcircle(GraphList *g){
    vector<int> visited(g->numVertex, 0);

    for(int i = 0; i < g->numVertex; i++){
        VertexNode currentNode = g->adjList[i];
        if(visited[currentNode.value] == 0){
            if(dfs(currentNode.value, visited, g)){
                cout << "has circle\n";
                return;
            }
        }
    }
    cout << "no circle\n";
}
```