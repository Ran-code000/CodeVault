# 并查集

## 并查集必备知识点

    1. 并查集是一种用于处理不相交集合（disjoint sets）合并与查询的问题 的数据结构。它支持以下两种基本操作：

        （1）find(x)：找到该元素所在集合的根节点
        （采用路径压缩优化）————> “扁平化”，将路径上的所有节点直接连接到根节点
        
![1](https://qcdn.itcharge.cn/images/20240513154759.png)

        （2）union(x, y)：将元素 x 和元素 y 所在的集合合并
        （采用按秩合并优化）————> 避免树的高度过大，从而提高查询效率

![1](https://qcdn.itcharge.cn/images/20240513154814.png)

    2. 并查集的核心是 集合的表示，它通过 树结构 来表示集合之间的关系。
   
        并查集的树结构：

        （1）每个集合都可以表示为一棵树：
        （2）根节点：表示集合的代表元素。
        （3）子节点：表示属于该集合的其他元素。
    
## 代码实现

### 查：采用路径压缩优化

```cpp
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]); 
    return parent[x];
}
```

### 并：采用按秩合并优化

```cpp
void unionSets(int x, int y)
{
  int rootX = find(x);
  int rootY = find(y);

  if (rootX != rootY)
  {
    if (rank[rootX] < rank[rootY])
    {
      parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
      parent[rootY] = rootX;
    }
    else
    {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
  }
}
```

## 经典例题 ———— 判断一个图是否构成树

### 思路：

    一个图如果可以构成树必然满足两个条件：

    （1）边数 == 节点数 - 1；(m == n - 1)

    （2）无环性 (hasCycle(edges, n) == false)

        判断 edges 中的每条边的两个顶点是否在同一集合中(connected(x, y, dsu))

        如果已经在同一集合中说明，再加入这条边会构成环，所以 return false; 即存在环不能构成树

        如果还不在同一集合中，则加入这条边（unionSets(x, y)）

### 题目描述

```txt
判断一个图是否构成树

问题描述
给定一个无向图，判断该图是否构成树。

输入
输入有若干测试样例。第一行是测试样例个数，接下来若干测试样例。
每个测试样例的第一行是结点数n，而且结点用1, 2, ..., n编号。
第二行是边数m，接下来是m个结点对。

输出
如果一个图是树，则打印"YES"，否则打印"NO"。每个输出占一行。

输入样例
4

3
2
1 2
2 3

3 
2
1 3
3 2

3
3
1 2
2 3
1 3

3
1
2 3
​
输出样例
YES
YES
NO
NO
```

```cpp
#include <iostream>
#include <vector>
using namespace std;

class DisjointSet
{
private:
  vector<int> parent;
  vector<int> rank;

public:
  // 构造函数
  DisjointSet(int size) : parent(size), rank(size, 0)
  {
    for (int i = 0; i < size; ++i)
    {
      parent[i] = i; // 每个节点是它自己的父节点
    }
  }

  // 查
  int find(int x)
  {
    if (parent[x] != x)
      parent[x] = find(parent[x]); // 路径压缩
    return parent[x];
  }

  // 并
  void unionSets(int x, int y)
  {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
    {
      if (rank[rootX] < rank[rootY])
      {
        parent[rootX] = rootY;
      }
      else if (rank[rootX] > rank[rootY])
      {
        parent[rootY] = rootX;
      }
      else
      {
        parent[rootY] = rootX;
        rank[rootX]++;
      }
    }
  }
};

// 判断两个节点是否在同一集合中
bool connected(int x, int y, DisjointSet &dsu)
{
  return dsu.find(x) == dsu.find(y);
}

// 判断图中是否存在环
bool hasCycle(vector<vector<int>> &edges, int n)
{
  DisjointSet dsu(n + 1);

  for (const auto &edge : edges)
  {
    int x = edge[0];
    int y = edge[1];

    // 如果两个节点已经连通，说明图中有环
    if (connected(x, y, dsu))
      return true;
    // 否则，合并两个集合
    else
      dsu.unionSets(x, y);
  }

  // 如果遍历所有边都没有发现环，返回false
  return false;
}

// 判断一个图是否构成树
bool validTree(vector<vector<int>> &edges, int n)
{
  // 条件(1)                       //条件（2）
  return edges.size() == n - 1 && hasCycle(edges, n) == false;
}

// 测试函数
int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++)
    {
      int a, b;
      cin >> a >> b;
      edges[i] = {a, b};
    }
    if (validTree(edges, n))
    {
      cout << "YES\n";
    }
    else
    {
      cout << "NO\n";
    }
  }
  return 0;
}


```

