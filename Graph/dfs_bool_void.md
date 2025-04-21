# dfs 的两种写法

在看之前实现图的遍历 dfs 和拓扑排序 dfs 实现的代码的时候的感悟

## 图的遍历 dfs 和拓扑排序 dfs 的区别

    0 → 1
    ↓   ↓
    2 → 3

图的邻接表表示：

    adjList[0] = {1, 2};
    adjList[1] = {3};
    adjList[2] = {3};
    adjList[3] = {};


1. 正常的 DFS 遍历：
   
    从节点 0 开始执行 DFS，假设我们按照邻接表的顺序遍历：

    从节点 0 开始，访问 0，然后访问 0 的邻接节点 1 和 2

    从节点 1 开始，访问 1，然后访问 1 的邻接节点 3

    从节点 3 开始，访问 3，发现没有邻接节点

    回到节点 1，再回到节点 0，访问 2

    从节点 2 开始，访问 2，然后访问 2 的邻接节点 3（但 3 已经访问过了）

    DFS 遍历的顺序：0 -> 1 -> 3 -> 2

2. 拓扑排序的 DFS 遍历：
  
    在拓扑排序中，我们使用栈存储节点，并确保先访问所有邻接节点再加入栈

    从节点 0 开始，访问 0，并标记为“正在访问”

    访问 0 的邻接节点 1，并标记为“正在访问”

    访问 1 的邻接节点 3，并标记为“正在访问”

    节点 3 没有邻接节点，标记为“已访问”，并将 3 放入栈中

    回到节点 1，标记为“已访问”，并将 1 放入栈中

    回到节点 0，访问 2，并标记为“正在访问”

    访问 2 的邻接节点 3（已访问过），因此直接标记 2 为“已访问”，并将 2 放入栈中

    回到节点 0，标记为“已访问”，并将 0 放入栈中

    拓扑排序的顺序：3 -> 1 -> 2 -> 0

### 总结两者的区别

DFS 遍历按照遇到的第一个未访问的邻接节点进行递归访问， ***直接记录*** 节点的访问顺序

拓扑排序要求节点在加入结果时要等到其 ***所有邻接节点被完全访问*** 过，因此节点的加入顺序是倒序的（即后序遍历）

## 代码

### 原 dfs 遍历代码

```cpp
void MyGraph::dfsVisit(int vertex, vector<bool>& visited, vector<int>& traversal) 
{
    visited[vertex] = true;
    traversal.push_back(vertex);
    
    for (const auto& edge : adjList[vertex])
        if (!visited[edge.first])
            dfsVisit(edge.first, visited, traversal); 
}

void MyGraph::DFS(int startVertex) 
{
    vector<bool> visited(n, false); 
    vector<int> traversal; 

    dfsVisit(startVertex, visited, traversal);
   
    for (int vertex : traversal) 
        cout << vertex << " ";
    cout << endl;
}
```

### 拓扑排序的 dfs 实现

```cpp
bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited, stack<int> &result)
{
    // 当前节点正在访问，图中有环
    if (visited[node] == 1)
        return false; 
    // 当前节点已经访问过
    if (visited[node] == 2)
        return true; 

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中
    visited[node] = 1; 

    for (int neighbor : adj[node])
        // 2. 如果访问到某个已经在 “ 访问中 ” 状态的节点，则说明图中存在环，无法进行拓扑排序
        if (!dfs(neighbor, adj, visited, result))
            return false;
    

    // 3. DFS 完成后，标记节点为“已访问”，并将节点加入到结果栈（或者队列）中
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

    // 1. 对每个未被访问的节点执行 DFS，标记该节点为访问中
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

想到如果同样对 dfs 遍历的返回值改为 bool 值也可以写成

```cpp
bool MyGraph::dfsVisit(int vertex, vector<bool> &visited, vector<int> &traversal)
{
  if (visited[vertex])
    return true;
  
  visited[vertex] = true;      
  traversal.push_back(vertex); 
  
  for (const auto &edge : adjList[vertex])
    if (!dfsVisit(edge.first, visited, traversal))
      return false;
    
  return true;
}

void MyGraph::DFS(int startVertex)
{
  vector<bool> visited(n, false); 
  vector<int> traversal;          
  if (dfsVisit(startVertex, visited, traversal))
  {
    cout << "DFS Traversal: ";
    for (int vertex : traversal)
    {
      cout << vertex << " ";
    }
    cout << endl;
  }
}

```