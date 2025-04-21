#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <vector>
#include <list>
class Graph{
    int VertexNum;
    vector<list<pair<int, int>>> adjList;
public:
    Graph(int n) : VertexNum(n){}
    void addEdge(int u, int v);
    void addVertex();
    void print();
    void getVertexNum();
    void dfs();
    void bfs()
};

#endif