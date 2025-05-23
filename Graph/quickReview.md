# dfs 和拓扑排序

    dfs 遍历类比拓扑排序遍历记，最开始 dfs 用 void 返回类型，拓扑排序用 bool 返回类型，其实 dfs 也可以改为 bool 返回类型（判断递归结束的条件 == ！进入递归的条件 ————> 可以将递归函数放到 if 判断条件中）

    dfs 直接处理节点，拓扑排序考虑节点先后顺序（节点在遍历完其所有邻接节点才加入结果） 

# 最短路径

    dijkstra，Bellman-Ford，Floyd-Warshall

    单源：dijkstra（贪心）    Bellman-Ford（动态规划，负权边）
          每次选最小          V - 1 次松弛，最后一次松弛判环

    多源：Floyd-Warshall（动态规划）
          O(V ^ 3)

## 是否需要判断路径是否存在

    dijkstra 不需要，每次选最小路径权重，最小路径权重路径必然存在
    
    Bellman-Ford，Floyd-Warshall 需要，遍历所有顶点对，不知道该两点间存不存在路径


# 最小生成树

    Prim，Kruskal

    加点：Prim（代码实现 ‘==’ dijkstra ：只有 distance 和 weight 表示内容不同）

    加边：Kruskal（边排升序，遍历边，判断两端点是否在同一集合中（并查集））

## 遍历完是否标记 visit 数组

    标记：
    bfs 标记：保证每个点只遍历一遍

    不标记：
    dijkstra，对所有邻接节点只更新，当所有的邻接节点都更新完，该节点才算访问完毕
    Prim(同理 dijkstra)

## 负权边

    dijkstra：包含该点的路径 必然比 不包括该点的路径 长，因为无负权边，所以每次只对该点所有邻接节点做一次松弛操作，不走回头路（自然需要 visit 数组）

    Bellman-Ford：包含该点的路径 不一定比 不包括该点的路径 长，因为可能存在负权边，虽然每次只对该点所有邻接节点做一次松弛操作，但最多对该点进行 V - 1 次（动态规划：不需要 visit 数组）

## 贪心算法 动态规划

    贪心算法，搜索：需要 visit 数组

    动态规划：不需要 visit 数组



