#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <functional>
#include <chrono>
#include <stack>
//#include "MeasureTime.h"
using namespace std;
class MyGraph{
    int numVertices;//顶点数量
    vector<list<pair<int, int>>> adjList;//邻接表来储存图，每个顶点的邻接表是一个存储了与该顶点相邻的顶点及其权重的列表

    //用于并查集（Union-Find）算法中的“路径压缩”查找操作。它递归地查找某个顶点的根，并且在查找过程中把该路径上的所有顶点直接连接到根，提高后续查找效率
    //找到 vertex 所属集合的根节点
    int find(vector<pair<int, int>>& forest, int vertex){
        //forest[vertex].second 表示顶点 vertex 的父节点。如果当前顶点的父节点不是它自己，说明它不是根节点。
        //在递归返回后，路径压缩的核心操作发生：将 vertex 直接连接到根节点。这一步显著提高了未来查找的效率，因为路径被压缩了
        if(forest[vertex].second != vertex) forest[vertex].second = find(forest, forest[vertex].second);
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
    MyGraph(int vertices) : numVertices(vertices), adjList(vertices){}//初始化图，指定顶点数量，并为每个顶点创建空的邻接表。
    void addVertex();
    void addEdge(int src, int dest, int weight = 1);
    void removeVertex(int vertex);
    void removeEdge(int src, int dest);
    vector<int> getNeighbors(int vertex);
    //遍历
    void DFS(int startVertex);
    void BFS(int startVertex);
    //最短路径
    void Dijkstra(int startVertex);
    void Dijkstra_withOptimize(int startVertex);//Optimizze by priority_queue
    void FloydWarshall();
    //最小生成树
    void Prim();
    void Kruskal();
    void TopologicalSort();  // New method for Topological Sort
    void BellmanFord(int startVertex);  // New method for Bellman-Ford Algorithm
    void TarjanSCC();  // New method for finding SCCs
    void CriticalPath();  // New method for Critical Path Method

    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Vertex " << i << ": ";
            for (auto const &neighbor : adjList[i]) cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            cout << endl;
        }
    }
    void drawGraph() {
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
//添加一个新的顶点，方法是调整邻接表的大小，并增加顶点总数numVertices
void MyGraph::addVertex(){ adjList.resize(numVertices++);}//注意：图的顶点数量增加，但并没有与其他顶点连接的边。
//在两个顶点之间添加一条边，同时设置边的权重
void MyGraph::addEdge(int src, int dest, int weight){
    //在邻接表中，对于无向图，边需要记录在两个顶点的邻接表中。
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight});
}
//删除某个顶点及与其相关的所有边（清空该顶点的邻接列表，并从其他顶点的邻接列表中移除所有与该顶点相关的边）
//！！！！！
//1. remove_if 标记删除：首先将所有与要删除的顶点相关的边标记为删除。
//2. erase 真正删除：然后使用 erase 来删除 remove_if 标记的元素。
//3. 删除顶点：最后，将整个顶点及其邻接表从 adjList 中移除
void MyGraph::removeVertex(int vertex){
    // 清空该顶点的邻接表
    adjList[vertex].clear();
    // 从其他顶点的邻接表中删除与该顶点相关的所有边
    for(auto& list : adjList){
    //remove_if 并不会真的删除元素，而是将所有不满足条件的元素移到容器的前面部分，并返回一个指向第一个被“移除”元素的迭代器。
    //remove_if 只会重新排列元素，而不会改变容器的大小。要从容器中真正删除多余的元素，必须调用 erase。所以它们通常一起使用，被称为“erase-remove 习惯用法”。
    //用法分解：
    //remove_if(list.begin(), list.end(), condition)：将不满足条件的元素移到容器前面，返回第一个满足条件的元素的迭代器。
    //list.erase(start_iterator, end_iterator)：从容器中删除从 start_iterator 到 end_iterator 之间的元素。
        list.erase(remove_if(list.begin(), list.end(), [vertex](const pair<int, int>& edge){ return edge.first == vertex;}), list.end());
    }
    // 最后从邻接表中删除这个顶点
    adjList.erase(adjList.begin() + vertex);
    numVertices--;
}
//从两个顶点的邻接表中移除一条边（通过遍历每个顶点的邻接表，找到并移除对应的邻接关系）
void MyGraph::removeEdge(int src, int dest){
    // 不严谨
    // adjList[src].remove_if([dest](pair<int, int>& edge){ return edge.first == dest;});
    // adjList[dest].remove_if([src](pair<int, int>& edge){ return edge.first == src;});
    adjList[src].erase(remove_if(adjList[src].begin(), adjList[src].end(), [dest](const pair<int, int>& edge){return edge.first == dest;}), adjList[src].end());
    adjList[dest].erase(remove_if(adjList[dest].begin(), adjList[dest].end(), [src](const pair<int, int>& edge){ return edge.first == src;}), adjList[dest].end());
}
//返回指定顶点的所有邻居顶点。
vector<int> MyGraph::getNeighbors(int vertex){
    vector<int> neighbors;
    //通过遍历该顶点的邻接表，收集所有相邻的顶点。
    for(const auto &edge : adjList[vertex]) neighbors.push_back(edge.first);
    return neighbors;
}
//遍历
//从给定的起始顶点进行深度优先搜索（DFS）
void MyGraph::DFS(int startVertex){
    vector<bool> visited(numVertices, false);//标记数组，记录顶点是否已被访问
    vector<int> traversal;//用于存储遍历过程中访问的顶点（路径）

    //定义一个名为dfsVisit的递归Lambda函数，接受一个顶点作为参数。
    //function 是 C++ 标准库中的一个类模板，允许你存储可调用对象（如函数指针、lambda 表达式等）。void(int) 指定这个函数不返回任何值（void），并且接受一个 int 类型的参数
    //这里存储的可调用对象 dfsVisit 是函数指针对象

    //[&](int vertex) 是 lambda 表达式
    //使用了 lambda 表达式来构造一个 function<void(int)>类模板的函数指针对象。这个对象可以接受一个整数参数并且不返回值，lambda 表达式通过 [&] 捕获外部变量（如 visited 和 traversal）的引用，便于在递归中使用
    //& 会捕获外部作用域中的所有变量，以引用的方式（在这个例子中是 visited 和 traversal）。这种捕获方式便于在递归调用中保持状态
    function<void(int)> dfsVisit = [&](int vertex){
        visited[vertex] = true;
        traversal.push_back(vertex);
        for(const auto& edge : adjList[vertex]) if(!visited[edge.first]) dfsVisit(edge.first);
    };
    dfsVisit(startVertex);
    for(int vertex : traversal) cout << vertex << " ";
    cout << endl;
    /*
    使用 lambda 表达式的主要好处在于简化代码和提高可读性。
    使得递归函数 dfsVisit 可以直接在 DFS 方法内部定义，这样就能方便地捕获外部的状态（如 visited 和 traversal）而不需要额外的参数
    否则：
    void MyGraph::DFS(int startVertex) {
        vector<bool> visited(numVertices, false); // 标记数组
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
//从给定的起始顶点进行广度优先搜索（BFS）。
void MyGraph::BFS(int startVertex){
    vector<bool> visited(numVertices, false);
    queue<int> queue;
    //起始顶点标记入队
    visited[startVertex] = true;
    queue.push(startVertex);
    while(!queue.empty()){
        int currentVertex = queue.front();
        queue.pop();
        cout << currentVertex << " ";
        //遍历当前顶点的邻接表，找到未被访问过的压入队列
        for(const auto& edge : adjList[currentVertex]) if(!visited[edge.first]) visited[edge.first] = true, queue.push(edge.first);
    }
    cout << endl;
}
//求最短路径
//Dijkstra 是找某一点（起始点）到其余各个点的最短路径
//This Dijkstra's implementation uses greedy selection to choose the next vertex with the smallest tentative distance.
//The time complexity is O(V^2)
void MyGraph::Dijkstra(int startVertex){
    vector<bool> visited(numVertices, false);
    vector<int> distances(numVertices, numeric_limits<int>::max());//the maximum possible integer value
    vector<int> prev(numVertices, -1);

    distances[startVertex] = 0;
    for(int i = 0; i < numVertices - 1; i++){
        int now_minDistance = numeric_limits<int>::max();
        int now_minVertex = -1;
        //Selecting the Unvisited Vertex with Minimum Distance
        for(int j = 0; j < numVertices; j++) if(!visited[j] && distances[j] < now_minDistance) now_minDistance = distances[j], now_minVertex = j;
        //Mark the Vertex as Visited
        visited[now_minVertex] = true;
        //Updating Distances for Neighboring Vertices
        for(const auto& pair : adjList[now_minVertex]){
            //Relaxation （松弛操作）
            if(distances[now_minVertex] + pair.second < distances[pair.first]) distances[pair.first] = distances[now_minVertex] + pair.second, prev[pair.first] = now_minVertex;
            //the prev array is also updated to store the current vertex (now_minVertex) as the predecessor of the neighboring vertex
        }
    }
    for(int i = 0; i < numVertices; i++) if(i != startVertex) cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
    /*
    If the graph has more vertices or edges, an optimized version of Dijkstra's algorithm using a priority queue (like a min-heap) can reduce the time complexity to O((V + E) log V), where E is the number of edges.
    details is below
    */
}
/*
To optimize Dijkstra's algorithm using a priority_queue in C++, we can significantly reduce the time complexity. 
The unoptimized version of Dijkstra iterates through all vertices in a linear scan to find the unvisited vertex with the smallest distance, leading to an overall time complexity of (O(V^2)). 
By using a priority_queue, we can bring this down to (O((V + E) \log V)), where (V) is the number of vertices and (E) is the number of edges. 
The priority queue (min-heap) allows us to efficiently extract the minimum distance vertex in (O(\log V)) time
*/
void MyGraph::Dijkstra_withOptimize(int startVertex){
    // Step 1: Initialization
    vector<bool> visited(numVertices, false); // to track visited vertices
    vector<int> distances(numVertices, numeric_limits<int>::max()); // store shortest path to each vertex
    vector<int> prev(numVertices, -1); // to store the previous vertex in the shortest path

    // Priority queue stores pairs of (distance, vertex), sorted by smallest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Push the start vertex with distance 0 into the priority queue
    // distances[startVertex] = 0;
    pq.push({0, startVertex});
    distances[startVertex] = 0; // distance to start vertex is 0

    // for(int i = 0; i < numVertices - 1; i++){
    while(!pq.empty()){
        //int now_minDistance = numeric_limits<int>::max();
        //int now_minVertex = -1;
        int now_minDistance = pq.top().first;
        int now_minVertex = pq.top().second;
        pq.pop();

        //for(int j = 0; j < numVertices; j++) if(!visited[j] && distances[j] < now_minDistance) now_minDistance = distances[j], now_minVertex = j; //don't need amymore

        //visited[now_minVertex] = true;
        visited[now_minVertex] = true;

        for(const auto& neighbor : adjList[now_minVertex]){
            //int neighborDistance = distances[now_minVertex] + neighbor.second;
            int neighborDistance = now_minDistance + neighbor.second;

            //if(neighborDistance < distances[neighbor.first]) distances[neighbor.first] = neighborDistance, prev[neighbor.first] = now_minVertex;
            if(neighborDistance < distances[neighbor.first]) distances[neighbor.first] = neighborDistance, prev[neighbor.first] = now_minVertex, pq.push({neighborDistance, neighbor.first});
        }


    }
    for(int i = 0; i < numVertices; i++) if(i != startVertex) cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
}
//Floyd-Warshall 是找到任意两点之间的最短路径
//Floyd-Warshall 是一种动态规划算法，用于求解任意两点之间的最短路径
//时间复杂度为 (O(V^3))，其中 (V) 是顶点数量。这个算法的原理是通过引入中间节点，逐步优化路径
void MyGraph::FloydWarshall(){
    //创建一个二维向量 distances 用来存储两点之间的路径长度，初始化为顶点数量 numVertices 大小，每个元素设置为无穷大（代表两点之间没有路径）
    vector<vector<int>> distances(numVertices, vector<int>(numVertices, numeric_limits<int>::max()));
    //创建一个二维向量 prev 用来存储路径的前驱节点，用于之后路径重建，初始化为 -1
    vector<vector<int>> prev(numVertices, vector<int>(numVertices, -1));
    //所有节点到自己的距离为 0，因此将 distances[i][i] 设为 0。
    for(int i = 0; i < numVertices; i++) distances[i][i] = 0;
    //初始化相邻节点之间的距离。遍历每个节点 i 的邻接表 adjList[i]，将边的权重 edge.second 设置为相应的 distances[i][edge.first]，并将 prev[i][edge.first] 设置为 i，表示 i 是 edge.first 的前驱。
    for(int i = 0; i < numVertices; i++)
        for(const auto& edge : adjList[i])
            distances[i][edge.first] = edge.second, prev[i][edge.first] = i;
    // Floyd-Warshall 的核心！！！
    //通过引入中间节点 k，检查从节点 i 经过 k 再到 j 的路径是否比 i 直接到 j 更短。如果是，则更新 distances[i][j] 和 prev[i][j]
    for(int k = 0; k < numVertices; k++)
        for(int i = 0; i < numVertices; i++)
            for(int j = 0; j < numVertices; j++)
               if(distances[i][k] != numeric_limits<int>::max() && distances[k][j] != numeric_limits<int>::max() && distances[i][k] + distances[k][j] < distances[i][j])
                    distances[i][j] = distances[i][k] + distances[k][j], prev[i][j] = prev[k][j];
    //输出所有顶点对之间的最短路径
    for(int i = 0; i < numVertices; i++)
        for(int j = 0; j < numVertices; j++) 
            if(i != j) cout << "Vertex " << i << " to " << j << " distance is " << distances[i][j] << endl;             
}
//最小生成树
//从一个起始点开始，逐步选择与当前生成树相连的、权重最小的边，直到所有节点都被包含。其时间复杂度是 (O(V^2))，适用于稠密图
//过程非常类似于 Dijkstra 算法
//(只有 distance 数组和 weight 数组保存的值的意义不同 ： Dijkstra 保存从该点到起始点最短路径长度，Prim 保存已选集合和未选集合之间最短的边权)
void MyGraph::Prim(){
    vector<bool> visited(numVertices, false);
    //创建一个向量 weight，记录每个节点与生成树的最小连接权重，初始值为无穷大
    vector<int> weight(numVertices, numeric_limits<int>::max());
    //prev 向量记录最小生成树中每个节点的父节点，初始值为 -1
    vector<int> prev(numVertices, -1);
    //设置起始节点的权重为 0，表示从第一个节点开始构建生成树。
    weight[0] = 0;
    for(int i = 0; i < numVertices; i++){
        int minVertex = -1;
        int minWeight = numeric_limits<int>::max();
        //从尚未加入生成树的节点中，找到权重最小的节点 minVertex
        for(int i = 0; i < numVertices; i++) if(!visited[i] && weight[i] < minWeight) minWeight = weight[i], minVertex = i;
        //将该节点加入最小生成树，并增加已加入节点的计数。
        visited[minVertex] = true;
        //遍历 minVertex 的邻接节点，更新连接权重，如果当前邻接节点的权重小于之前记录的最小权重，则更新权重并记录其父节点
        for(const auto& pair : adjList[minVertex]) if(!visited[pair.first] && pair.second < weight[pair.first]) weight[pair.first] = pair.second, prev[pair.first] = minVertex;
        for(int i = 1; i < numVertices; i++) cout << "Edge " << prev[i] << " - " << i << " with weight " << weight[i] << endl;
    }
}
//按照边的权重进行排序，每次选择权重最小的边，只要不形成环。
//时间复杂度是 (O(E \log E))，适用于稀疏图
void MyGraph::Kruskal(){
    //创建一个存储边的向量 edges，每个边由权重和两个顶点组成
    vector<pair<int, pair<int, int>>> edges;
    for(int i = 0; i < numVertices; i++)
        for(const auto& edge : adjList[i]) 
            edges.push_back({edge.second, {i, edge.first}});
    //按照边的权重升序排序。
    sort(edges.begin(), edges.end());
    //初始化一个并查集 forest，用于判断不同的节点是否属于同一个连通分量（是否形成环）。
    //forest 保存每个顶点和其父节点
    vector<pair<int, int>> forest(numVertices);
    for(int i = 0; i < numVertices; i++) forest[i] = {i, i};
    //遍历所有边，如果两个节点不属于同一个集合（不形成环），则将该边加入生成树，并合并这两个集合。当加入的边数达到 (V-1) 时，最小生成树构建完成
    int numEdges = 0;
    for(const auto& edge : edges){
        int root1 = find(forest, edge.second.first);
        int root2 = find(forest, edge.second.second);
        if(root1 != root2){
            forest[root1] = {root1, root2};
            numEdges++;
            cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
            if(numEdges == numVertices - 1) break;
        }
    }
    //错误写法
    //没有输出的原因是因为条件 if(root1 != root2) 不成立，因为此时所有边都已连接，形成了一个最小生成树（MST），没有剩余边可以输出。
    // for(const auto& edge : edges){
    //     int root1 = find(forest, edge.second.first);
    //     int root2 = find(forest, edge.second.second);
    //     if(root1 != root2) cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
    // }

}
//拓扑排序
void MyGraph::TopologicalSort(){
    vector<bool> visited(numVertices, false);  // 记录每个顶点是否访问过
    stack<int> topoStack;  // 存储拓扑排序结果的栈

    // 使用 Lambda 函数实现的递归 DFS
    function<void(int)> topologicalDFS = [&](int vertex){
        visited[vertex] = true;
        for(const auto& pair : adjList[vertex]) if(!visited[pair.first]) topologicalDFS(pair.first);
        // 将该顶点加入栈，表示它的所有邻居已经处理完毕
        topoStack.push(vertex);
    };
    // 对图中的每个顶点进行 DFS，确保所有连通分量都被遍历
    for(int i = 0; i < numVertices; i++) if(!visited[i]) topologicalDFS(i);
    cout << "Topological Sort: ";
    while(!topoStack.empty()) cout << topoStack.top() << " ", topoStack.pop();
    cout << endl;
}
// Bellman-Ford Algorithm
// Bellman-Ford算法用于在 带负权边的图中计算单源最短路径，即从给定起点到其他所有顶点的最短距离。
// 与Dijkstra算法不同，Bellman-Ford能够处理图中存在负权重边的情况。它的时间复杂度是 (O(V \times E))，其中 (V) 是顶点数，(E) 是边数。
// Bellman-Ford算法的主要思想是通过松弛操作（Relaxation），逐步逼近最短路径。松弛操作会不断尝试更新路径，直到无法再优化路径为止。
// Bellman-Ford执行最多 (V-1) 次松弛操作，其中 (V) 是图的顶点数。最后通过一次额外的检查判断是否存在 负权重环（negative weight cycle）。
void MyGraph::BellmanFord(int startVertex){
    vector<int> distances(numVertices, numeric_limits<int>::max());
    distances[startVertex] = 0;

    for(int i = 0; i < numVertices - 1; i++)
        for(int j = 0; j < numVertices; j++)
            for(const auto& pair : adjList[j])
                //Relaxation 操作(n - 1)times
                if(distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first]) distances[pair.first] = distances[j] + pair.second;
    // Check for negative weight cycles
    for(int j = 0; j < numVertices; j++)
        for(const auto& pair : adjList[j])
            //Relaxation 操作 1 times
            if(distances[j] != numeric_limits<int>::max() && distances[j] + pair.second < distances[pair.first]){ cout << "Graph contains a negative weight cycle!" << endl; return;}
    for(int i = 0; i < numVertices; i++) if(i != startVertex) cout << "vertex " << i << " distance from " << startVertex << " is " << distances[i] << endl;
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
// Tarjan's Algorithm for finding SCCs
// Tarjan 算法是一种用于找出有向图中的强连通分量（SCC）的算法。
// 其基本原理是通过深度优先搜索（DFS）来遍历图，并使用两个数组来跟踪节点的发现时间和最低可达节点，从而识别出强连通分量。
void MyGraph::TarjanSCC(){
    // disc记录每个节点被访问的时间戳，low记录当前节点可追溯到的最小时间戳
    vector<int> disc(numVertices, -1), low(numVertices, -1);
    //存储当前访问的节点
    stack<int> stk;
    //用于标记节点是否在栈中，防止重复入栈。
    vector<bool> visited(numVertices, false);
    //初始化一个时间计数器time，用于跟踪访问节点的顺序
    int time = 0;

    //定义一个递归函数SCCDFS，接受一个整数参数u，表示当前访问的节点。
    //使用function和lambda表达式来实现递归。
    function<void(int)> SCCDFS = [&](int vertex){
        //访问节点 vertex ，同时更新 disc 和 low 数组为当前时间戳 time
        disc[vertex] = low[vertex] = ++time;
        //将节点 vertex 压入栈中，表示它是当前路径的一部分
        stk.push(vertex);
        //将节点 vertex 标记为在栈中
        visited[vertex] = true;

        //遍历邻接列表 adjList 中与节点 vertex 相连的每个邻接节点。
        for(const auto& pair : adjList[vertex]){
            //如果节点 pair.first 尚未被访问（即disc[pair.first]为-1），则递归访问它
            //更新low[vertex]，检查 vertex 的 low 值是否需要更新为邻接节点 pair.first 的 low 值
            if(disc[pair.first] == -1) SCCDFS(pair.first), low[vertex] = min(low[vertex], low[pair.first]);
            //如果节点 vertex 已在栈中，则表示 vertex 是当前 SCC 的一部分。
            //更新low[vertex]，以便记录到达 pair.first 的时间戳
            else if(visited[pair.first]) low[vertex] = min(low[vertex], disc[pair.first]);
        }

        // If vertex is the head node of an SCC
        //如果当前节点 vertex 的 low 值等于其 disc 值，则 vertex 是当前强连通分量的根节点。
        if(low[vertex] == disc[vertex]){
            // 输出标记，表示即将打印一个强连通分量
            cout << "SCC: ";
            // 开始一个循环，直到栈顶元素为 vertex
            while(stk.top() != vertex){
                cout << stk.top() << " ";
                //将节点v标记为不在栈中并从栈中弹出
                visited[vertex] = false;
                stk.pop();
            }
            //打印根节点 vertex ，完成当前强连通分量的输出
            cout << vertex << endl;
            //将节点v标记为不在栈中并从栈中弹出
            visited[vertex] = false;
            stk.pop();
        }
    };
    //如果节点i尚未被访问，则调用SCCDFS
    for(int i = 0; i < numVertices; i++) if(disc[i] == -1) SCCDFS(i);
}
// Critical Path Method (CPM)
// Critical Path Method (CPM) 是一种用于项目管理的技术，它帮助确定项目中所有任务的最早完成时间以及最关键的任务路径（即关键路径）。
// 关键路径是决定项目最早完成时间的任务序列，如果这些任务中的任何一个延迟，项目的整体完成时间也会延迟。
// 从起点到终点的正向计算，确定每个任务的最早开始和最早完成时间；
// 通过从终点到起点的逆向计算，确定任务的最晚开始时间。
void MyGraph::CriticalPath(){
    vector<int> topoOrder;
    vector<int> earliestStart(numVertices, 0), latestStart(numVertices, numeric_limits<int>::max());

    // Topological sort to find the order of vertices
    vector<bool> visited(numVertices, false);
    function<void(int)> topologicalDFS = [&](int vertex){
        visited[vertex] = true;
        for(const auto& pair : adjList[vertex]) if(!visited[pair.first]) topologicalDFS(pair.first);
        topoOrder.push_back(vertex);
    };

    for(int i = 0; i < numVertices; i++) if(!visited[i]) topologicalDFS(i);

    reverse(topoOrder.begin(), topoOrder.end());

    // Forward pass to calculate earliest start times
    for(auto it = topoOrder.begin(); it != topoOrder.end(); it++)
        for(const auto& pair : adjList[*it])
            earliestStart[pair.first] = max(earliestStart[pair.first], earliestStart[*it] + pair.second);
      
    latestStart[topoOrder[0]] = earliestStart[topoOrder[0]];

    // Backward pass to calculate latest start times
    for(auto it = topoOrder.rbegin(); it != topoOrder.rend(); it++)
        for(const auto& pair : adjList[*it])
            latestStart[*it] = min(latestStart[*it], latestStart[pair.first] - pair.second);

    cout << "Critical Path: ";
    for(int vertex : topoOrder)
        for(const auto& pair : adjList[vertex])
            if(earliestStart[vertex] == latestStart[pair.first] - pair.second) cout << vertex << " -> " << pair.first << " (weight " << pair.second << "), ";
    cout << endl;
}
//text function
int main() {
    MyGraph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.printGraph();
    g.drawGraph();
    cout << "DFS:\n";
    g.DFS(0);
    cout << "BFS:\n";
    g.BFS(0);
    cout << "Dijkstra:\n";
    g.Dijkstra(0);
    cout << "Dijkstra_with_optimize:\n";
    g.Dijkstra_withOptimize(0);    
    cout << "Floyd-Warshall:\n";
    g.FloydWarshall();
    cout << "Prim:\n";
    g.Prim();
    cout << "Kruskal:\n";
    g.Kruskal();
    cout << "Topological Sort:\n";
    g.TopologicalSort();
    cout << "Bellman-Ford from Vertex 0:\n";
    g.BellmanFord(0);
    cout << "Finding SCCs using Tarjan's Algorithm:\n";
    g.TarjanSCC();
    cout << "Critical Path Method:\n";
    g.CriticalPath();
    // measureTime("Dijkstra", &MyGraph::Dijkstra, &g, 0);
    // measureTime("Dijkstra_with_optimize", &MyGraph::Dijkstra_withOptimize, &g, 0);
    // measureTime("FloydWarshall", &MyGraph::FloydWarshall, &g);
    // measureTime("Prim", &MyGraph::Prim, &g);
    // measureTime("Kruskal", &MyGraph::Kruskal, &g);
    // measureTime("TopologicalSort", &MyGraph::TopologicalSort, &g);
    // measureTime("BellmanFord", &MyGraph::BellmanFord, &g, 0);
    // measureTime("TarjanSCC", &MyGraph::TarjanSCC, &g);
    // measureTime("CriticalPath", &MyGraph::CriticalPath, &g);
    return 0;
}