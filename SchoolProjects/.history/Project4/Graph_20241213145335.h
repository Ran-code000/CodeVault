#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <vector>
#include <list>
class Graph{
    int VertexNum;
    vector<list<pair<int, int>>> adjList;
public:
    Graph(int n) : VertexNum(n), adjList(n + 1){}
    void addEdge(int u, int v, int w);
    void addVertex();
    void getVertexNum();
    void dfs();
    void bfs();
    void dijkstra();
};

#endif