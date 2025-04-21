#include "Graph.h"

void Graph::addEdge(int u, int v, int w){
    adjList[u].push_back({v, w});
}
void Graph::addVertex(){
    VertexNum++;
}
void Graph::print();
void Graph::getVertexNum();
void Graph::dfs();
void Graph::bfs();
void Graph::dijkstra();