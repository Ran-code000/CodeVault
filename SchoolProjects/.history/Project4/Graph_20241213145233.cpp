#include "Graph.h"

void Graph::addEdge(int u, int v, int w){
    adjList[u].push_back({v, w});
}
void Graph::addVertex();
void Graph::print();
void getVertexNum();
void dfs();
void bfs();
void dijkstra();