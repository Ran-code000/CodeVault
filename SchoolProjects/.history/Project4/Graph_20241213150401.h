#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <vector>
#include <list>
#include <queue>

class Graph
{
    int VertexNum;
    std::vector<std::list<std::pair<int, int>>> adjList;

public:
    Graph(int n) : VertexNum(n), adjList(n + 1) {}
    void addEdge(int u, int v, int w);
    void addVertex();
    void getVertexNum();
    void dfs(int start);
    void bfs(int start);
    void dijkstra(int src);
};

#endif