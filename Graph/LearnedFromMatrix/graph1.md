# 好题 + 收获

## problem 1 打开转盘锁

### 题目描述

```txt
打开转盘锁

问题描述
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字：'0','1','2','3','4','5','6','7','8','9'。每个拨轮可以自由旋转：例如把'9'变为'0'，'0'变为'9'。每次旋转都只能旋转一个拨轮的一位数字。

锁的初始数字为"0000"，一个代表四个拨轮的数字的字符串。

列表deadends包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。

字符串target代表可以解锁的数字，你需要给出最小的旋转次数。

输入
第一行为一组目标数字，第二行为死亡数字的组数N。接下来N行，每行记录了一组死亡数字。

输出
输出最小的旋转次数，如果无论如何不能解锁，输出-1。

示例输入
0202
5
0201
0101
0102
1212
2002
​
示例输出
6
​
提示
可能的移动序列为"0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。

注意"0000" -> "0001" -> "0002" -> "0102" -> "0202"这样的序列是不能解锁的，因为当拨动到"0102"时这个锁就会被锁定。
```

---

### 代码实现

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

unordered_map<string, bool> dead;
unordered_map<string, bool> visit;
int minStep = 0;
string target;

vector<string> nextStatus(string &currentString)
{
  vector<string> nextStatus;
  for (size_t i = 0; i < currentString.size(); i++)
  {
    string subString = currentString, addString = currentString;
    subString[i] = '0' + (subString[i] - '0' + 10 - 1) % 10;
    addString[i] = '0' + (addString[i] - '0' + 1) % 10;
    nextStatus.push_back(subString);
    nextStatus.push_back(addString);
  }
  return nextStatus;
}
int bfs()
{
  string start = "0000";

  if (dead[start] == true)
    return -1;

  queue<pair<string, int>> q;
  q.push({start, 0});
  visit[start] = true;

  while (!q.empty())
  {
    auto [currentString, currentStep] = q.front();
    q.pop();

    if (currentString == target)
      return currentStep;
    else
    {
      for (const string nextString : nextStatus(currentString))
      {
        if (nextString == target)
          return currentStep + 1;
        if (!dead[nextString] && !visit[nextString])
        {
          visit[nextString] = true;
          q.push({nextString, currentStep + 1});
        }
      }
    }
  }
  return -1;
}
int main()
{
  cin >> target;
  int n;
  cin >> n;

  while (n--)
  {
    string deadstring;
    cin >> deadstring;
    dead[deadstring] = true;
  }

  minStep = bfs();
  cout << minStep;
  return 0;
}
```

---

### 收获

题目一眼搜索， but 深搜 or 广搜？

最小的旋转次数 ——> 到达目标状态的最少步骤 ———> 求最短路径 ————> bfs

先拿出我们的 bfs 框架

![1](https://i-blog.csdnimg.cn/blog_migrate/2339de9fbe47ae0fe556b3cd2605be89.png)

```cpp
// bfs 框架

返回值 bfs(必要参数)
{
  // 队列，用于存储待处理的状态
  queue<搜索状态的类型> q;

  // 记录访问过的状态，避免重复处理
  bool visit[状态空间大小];            // 标记数组，大小根据题目调整
  memset(visit, false, sizeof(visit)); // 初始化为未访问

  // 初始化起始状态，标记为已访问
  q.push(起始状态);
  visit[起始状态] = true;

  // 步数计数器
  int steps = 0; // 记录当前的搜索步数

  // 开始 BFS 搜索
  while (!q.empty())
  {
    // 当前层的节点数量
    int levelSize = q.size();

    // 遍历当前层的所有节点
    for (int i = 0; i < levelSize; ++i)
    {
      // 获取当前状态
      搜索状态的类型 当前状态 = q.front();
      q.pop();

      // 检查是否已找到目标状态
      if (当前状态 == 目标状态)
      {
        return steps; // 返回最少步骤
      }
      else
      {
        // 获取当前状态的所有可能下一状态
        for (搜索状态的类型 下一个状态 : getNextStatus(当前状态))
        {
          // 如果下一个状态符合题目条件且未被访问过
          if (下一个状态符合条件(下一个状态) && !visit[下一个状态])
          {
            visit[下一个状态] = true; // 标记为已访问
            q.push(下一个状态);       // 将新状态加入队列
          }
        }
      }

      
    }

    // 增加步数，表示已经处理完当前层
    ++steps;
  }

  // 如果队列为空且未找到目标状态，返回无法到达目标时的返回值
  return 无法到达目标状态时的要求返回值;
}
```

ps：我习惯于将得到下一个状态单独抽象成一个方法 getNextStatus，可以提高代码的可维护性和可读性

```cpp
// 方法 getNextStatus
// 根据当前状态返回所有可能的下一步状态
std::vector<搜索状态的类型> getNextStatus(搜索状态的类型 当前状态)
{
  std::vector<搜索状态的类型> 下一个状态数组; // 用于保存所有下一步状态

  // 假设我们有一个从当前状态到所有邻接状态的操作
  for (每一个邻接的状态或者每一个可能的转换)
  {
    // 根据当前状态生成下一个状态
    搜索状态的类型 新状态 = 根据当前状态生成新状态(当前状态);

    // 这里可以加入判断条件，确保新状态符合要求
    if (新状态符合题目要求)
    {
      // 将符合条件的状态添加到数组中
      下一个状态数组.push_back(新状态);
    }
  }

  // 返回所有符合条件的下一个状态
  return 下一个状态数组;
}
```



## 收获

当顶点的值有特殊的值储存时，定义邻接表的方式

```cpp
#include <iostream>
#include <queue>
using namespace std;
#define MAXVEX 1000
// 边表节点
class EdgeNode
{
public:
  int adjvex; // 边指向哪个顶点的索引
  int weight;
  EdgeNode *next;
};
// 顶点表结构
class VertexNode
{
public:
  int value; // 顶点的值
  EdgeNode *firstedge;
};
// 图结构
class GraphList
{
public:
  VertexNode adjList[MAXVEX];
  int numVertex;
  int numEdges;
};
void createGraph(GraphList *g);

```

 `std::unordered_map<int, std::vector<Node>> adj;  `

当顶点的值就是索引值时，邻接表的定义邻接表的方式比较简单

```cpp
vector<list<pair<int, int>>> adj;
```

## 收获（dfs）

正确
```cpp
void deal(int u, int v, int w, Graph &g)
{
  // Only process when w is divisible by 3
  if (w % 3 != 0)
    return;

  // Split the edge into two parts, 2w/3 and w/3
  int a = 2 * w / 3; // First part
  int b = w / 3;     // Second part

  // Recursively break down the first part (2w/3)
  if (a % 3 == 0)
  {
    deal(u, v, a, g); // Recursive call for first part
  }
  else
  {
    g.addEdge(u, v, a); // Add edge if it's not divisible by 3
  }

  // Recursively break down the second part (w/3)
  if (b % 3 == 0)
  {
    deal(v, u, b, g); // Recursive call for second part
  }
  else
  {
    g.addEdge(v, u, b); // Add edge if it's not divisible by 3
  }
}
```

错误
```cpp
void deal(int u, int v, int w, Graph &g)
{
  if (w % 3 != 0)
    return;
  deal(u, v, 2 * w / 3, g);
  g.addEdge(u, v, 2 * w / 3);
  deal(v, u, w / 3, g);
  g.addEdge(v, u, w / 3);
}
```

第一段代码严格按照边的拆分逻辑，分别处理 a = 2 * w / 3 和 b = w / 3，确保递归到最深处时才判断是否需要添加边。
  理解：此时 a, b同级，都由 w 得到，类比二叉树

第二段代码在递归调用后立即判断 w 是否需要添加边，导致逻辑混乱和边的重复添加。
  不区分a, b导致 后面的 w / 3 依赖于 2 * w / 3，不正确

## 初始化数组

  对于未明确初始化的其余元素，C++ 会 自动初始化为 0。这是一种特殊的规则：当数组部分初始化时，未被明确初始化的元素会被自动填充为零
 
一维初始化 ： 
    
    1. 初始化为 0：
        `int a[n] = {0};` 等价于 `int a[n] = {0, 0, 0, ..., 0};`

       

    2. 初始化为 其他数字 ： 
    
        法一：fill(a.begin(), a.end(), 其他的数);

        法二：include 头文件 <cstring>，memset(a, -1, sizeof(a)); 
          （a：数组名；初始化整个数组为 -1）

          错误写法：int a[n][n] = {-1}; (只将第一个元素赋为 -1，其余的为 0)

二维初始化：

    法一： 使用迭代器初始化
   
    for (auto& row : a) 
        fill(row.begin(), row.end(), 5);  // 将每一行的所有元素都设置为 5
    

    法二： 使用指针初始化
   
    fill(&a[0][0], &a[0][0] + (n + 1) * (n + 1), -1);

    法三：include 头文件 <cstring>，memset(a, -1, sizeof(a)); 
      （a：数组名；初始化整个数组为 -1）

## 求连通分量

```txt
 图的连通性

题目描述
给定一个n个节点m条边的无向图G，节点编号从1到n，保证图中没有重边和自环。

现在，你要统计G的连通分量数目C，以及每个连通分量的大小（节点数目）。

输入描述
第1行包含两个整数n,m (2≤n≤10 
4
 ,1≤m≤2×10 
5
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的无向边。

输出描述
第一行，一个数字，表示图G的连通分量数目C。
第二行，包含C个整数，表示每个连通分量的大小，按照升序排列。

输入样例1
9 11
3 6
4 6
3 5
3 4
1 4
1 3
6 5
4 5
7 2
5 1
1 6
​
输出样例1
4
1 1 2 5
​
随机测试数据
子任务	平均占比	约束
子任务0	20%	n≤10,m≤20
子任务1	20%	n≤100,m≤200，且连通分量数目不超过2个
子任务2	60%	无约束
提示
在C++中，可以使用std::sort()和对整数数组按照升序或降序排列。

#include <algorithm>
#include <vector>

int main() {
  std::vector<int> arr;
  // ...
  std::sort(arr.begin(), arr.end()); // 升序排序
  std::sort(arr.begin(), arr.end(), greater<int>{}); // 降序排序
}
​

```

    方案：

    1. 初始化：创建一个数组或 visited 数组，记录每个节点是否被访问过。
    
    2. 遍历每个顶点：对于每一个未访问的顶点，启动一个深度优先搜索（DFS）或者广度优先搜索（BFS），将该连通分量中的所有节点标记为已访问。
    
    3. 计数连通分量：每当从一个未访问的顶点开始进行 DFS/BFS 时，说明找到一个新的连通分量，计数器加一。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

vector<bool> visit;
vector<int> res;

class Graph{
public:
    int vertexNum;
    vector<vector<int>> adj;
    Graph(int n) : vertexNum(n), adj(n + 1){
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
void dfs(int startVertex, int& _size, Graph& graph){
    vector<int> nowList = graph.adj[startVertex];
    for(size_t i = 0; i < nowList.size(); i++){
        if(!visit[nowList[i]]){
            visit[nowList[i]] = 1;
            _size++;
            dfs(nowList[i], _size, graph);
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    visit.resize(n + 1);
    while(m--){
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    for(int i = 1; i <= n; i++){
        if(!visit[i]){
            visit[i] = 1;
            int _size = 1;
            dfs(i, _size, graph);
            res.push_back(_size);
        }
    }
    cout << res.size() << endl;
    sort(res.begin(), res.end());
    for(size_t i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    return 0;
}
```

## 无向图可达性

并查集