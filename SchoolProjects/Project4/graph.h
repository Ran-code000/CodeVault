#ifndef GRAPH_H
#define GRAPH_H

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
    int getVertexNum();
    std::vector<int> &dfs(int start, std::vector<int> &res);
    std::vector<int> &bfs(int start, std::vector<int> &res);
    std::vector<std::pair<int, int>> &dijkstra(int src, std::vector<std::pair<int, int>> &);
    std::vector<std::vector<int>> &floyd(int src, std::vector<std::vector<int>> &);
};

#endif