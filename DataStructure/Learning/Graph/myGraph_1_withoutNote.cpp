#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <queue>
#include <functional>
#include <limits>
using namespace std;
class MyGraph{
    int numVertices;
    vector<list<pair<int, int>>> adjList;
    int find(vector<pair<int, int>> forest, int vertex){
        if(forest[vertex].second != vertex) forest[vertex].second = find(forest, forest[vertex].second);
        return forest[vertex].second;
    }
public:
    MyGraph(int vertices) : numVertices(vertices), adjList(numVertices){}
    void addVertex();
    void addEdge(int src, int dest, int weight = 1);
    void removeVertex(int Vertex);
    void removeEdge(int src, int dest);
    vector<int> getNeighbors(int vertex);
    void DFS(int startVertex);
    void BFS(int startVertex);
    void Dijkstra(int startVertex);
    void Dijkstra_withOptimize(int startVertex);
    void FloydWarshall();
    void Prim();
    void Kruskal();
    void printGraph(){
        for(int i = 0; i < adjList.size(); i++){
            cout << "Vertex " << i << ": ";
            for (auto const &neighbor : adjList[i]) cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            cout << endl;
        }
    }
    void drawGraph(){
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
void MyGraph::addVertex(){ adjList.resize(numVertices++);}
void MyGraph::addEdge(int src, int dest, int weight){
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight});
}
void MyGraph::removeVertex(int Vertex){
    adjList[Vertex].clear();
    for(auto& list : adjList)
        for(const auto& pair : list)
            if(pair.first == Vertex) list.remove(pair);
}
void MyGraph::removeEdge(int src, int dest){
    for(const auto& pair : adjList[src]) if(pair.first == dest) adjList[src].remove(pair);
    for(const auto& pair : adjList[dest]) if(pair.first == src) adjList[dest].remove(pair);
}
vector<int> MyGraph::getNeighbors(int vertex){
    vector<int> neighbors;
    for(const auto& pair : adjList[vertex]) neighbors.push_back(pair.first);
    return neighbors;
}
void MyGraph::DFS(int startVertex){
    vector<bool> visited(numVertices, false);
    vector<int> traversal;
    function<void(int)> dfs = [&](int vertex){
        visited[vertex] = true;
        traversal.push_back(vertex);
        for(const auto& pair : adjList[vertex]) if(!visited[pair.first]) dfs(pair.first); 
    };
    dfs(startVertex);
    for(int i = 0; i < numVertices; i++) cout << traversal[i] << " ";
    cout << endl;
}
void MyGraph::BFS(int startVertex){
    vector<bool> visited(numVertices, false);
    queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;
    while(!q.empty()){
        int nowVertex = q.front();
        q.pop();
        cout << nowVertex << " ";
        for(const auto& pair : adjList[nowVertex]) if(!visited[pair.first]) visited[pair.first] = true, q.push(pair.first);
    }
    cout << endl;
}
void MyGraph::Dijkstra(int startVertex){
    vector<bool> visited(numVertices, false);
    vector<int> distances(numVertices, numeric_limits<int>::max());
    vector<int> prev(numVertices, -1);
    distances[startVertex] = 0;
    for(int i = 0; i < numVertices - 1; i++){
        int minDistance = numeric_limits<int>::max();
        int minVertex = -1;
        for(int j = 0; j < numVertices; j++) if(!visited[j] && distances[j] < minDistance) minDistance = distances[j], minVertex = j;
        visited[minVertex] = true;
        for(const auto& pair : adjList[minVertex]) if(!visited[pair.first] && distances[minVertex] + pair.second < distances[pair.first]) distances[pair.first] = distances[minVertex] + pair.second, prev[pair.first] = minVertex;
    }
    for(int i = 0; i < numVertices; i++){
        cout << "Vertex " << i << " distance from " << startVertex << " is " << distances[i] << "     ";
        cout << "The path is: ";
        for(int j = i; j != -1; j = prev[j]) cout << j << " ";
        cout << endl;
    }
}
void MyGraph::Dijkstra_withOptimize(int startVertex){
    vector<bool> visited(numVertices, false);
    vector<int> distances(numVertices, numeric_limits<int>::max());
    vector<int> prev(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distances[startVertex] = 0;
    pq.push({0, startVertex});
    while(!pq.empty()){
        int minDistance = pq.top().first;
        int minVertex = pq.top().second;
        pq.pop();
        if(!visited[minVertex]){
            visited[minVertex] = true;
            for(const auto& pair : adjList[minVertex]) if(minDistance + pair.second < distances[pair.first]) distances[pair.first] = minDistance + pair.second, pq.push({distances[pair.first], pair.first}), prev[pair.first] = minVertex;
        }
    }
    for(int i = 0; i < numVertices; i++){
        cout << "Vertex " << i << " distance from " << startVertex << " is " << distances[i] << "    ";
        cout << "The path is:";
        for(int j = i; j != -1; j = prev[j]) cout << j << " ";
        cout << endl; 
    }
}
void MyGraph::FloydWarshall(){
    vector<vector<int>> distances(numVertices, vector<int>(numVertices, numeric_limits<int>::max()));
    vector<vector<int>> prev(numVertices, vector<int>(numVertices, -1));
    for(int i = 0; i < numVertices; i++) distances[i][i] = 0;
    for(int i = 0; i < numVertices; i++)
        for(const auto& pair : adjList[i])
            distances[i][pair.first] = pair.second;
    for(int k = 0; k < numVertices; k++)
        for(int i = 0; i < numVertices; i++)
            for(int j = 0; j < numVertices; j++)
                if(distances[i][k] != numeric_limits<int>::max() && distances[k][j] != numeric_limits<int>::max() && k != i && k != j && distances[i][k] + distances[k][j] < distances[i][j]) distances[i][j] = distances[i][k] + distances[k][j], prev[i][j] = prev[k][j];
    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(i == j) continue;
            cout << "Vertex " << i << " to " << j << " distance is " << distances[i][j] << "    ";
            cout << "The path is: ";
            for(int k = j; k != -1; k = prev[i][k]) cout << k << " ";
            cout << endl; 
        }
    }
}
void MyGraph::Prim(){
    vector<bool> visited(numVertices, false);
    vector<int> weight(numVertices, numeric_limits<int>::max());
    vector<int> prev(numVertices, -1);
    weight[0] = 0;
    for(int i = 0; i < numVertices - 1; i++){
        int minweight = numeric_limits<int>::max();
        int minVertex = -1;
        for(int i = 0; i < numVertices; i++) if(!visited[i] && weight[i] < minweight) minweight = weight[i], minVertex = i;
        visited[minVertex] = true;
        for(const auto& pair : adjList[minVertex]) if(!visited[pair.first] && pair.second < weight[pair.first]) weight[pair.first] = pair.second, prev[pair.first] = minVertex;
    }
    for(int i = 0; i < numVertices; i++){
        cout << "Vertex " << i << " weight is " << weight[i] << "     ";
        cout << "The path is: ";
        for(int j = i; j != -1; j = prev[j]) cout << j << " ";
        cout << endl;
    }
}
void MyGraph::Kruskal(){
    vector<pair<int, pair<int, int>>> edges;
    for(int i = 0; i < numVertices; i++)
        for(const auto& pair : adjList[i]) edges.push_back({pair.second, {i, pair.first}});
    sort(edges.begin(), edges.end());
    vector<pair<int, int>> forest(numVertices);
    for(int i = 0; i < numVertices; i++) forest[i] = {i, i};
    int numEdge = 0;
    for(const auto& edge : edges){
        int root1 = find(forest, edge.second.first);
        int root2 = find(forest, edge.second.second);
        if(root1 != root2){
            forest[root1] = {root1, root2};
            numEdge++;
            cout << "Edge " << edge.second.first << " - " << edge.second.second << " with weight " << edge.first << endl;
            if(numEdge == numVertices - 1) break;
        }
    }
}
int main() {
    MyGraph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.printGraph();
    g.drawGraph();

    auto start = chrono::high_resolution_clock::now();
    cout << "DFS:\n";
    g.DFS(0);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "DFS runnning time: " << duration << "μs" << endl;

    auto start0 = chrono::high_resolution_clock::now();
    cout << "BFS:\n";
    g.BFS(0);
    auto end0 = chrono::high_resolution_clock::now();
    auto duration0 = chrono::duration_cast<chrono::microseconds>(end0 - start0).count();
    cout << "BFS runnning time: " << duration0 << "μs" << endl;

    auto start1 = chrono::high_resolution_clock::now();
    cout << "Dijkstra:\n";
    g.Dijkstra(0);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "Dijkstra runnning time: " << duration1 << "μs" << endl;
    
    auto start2 = chrono::high_resolution_clock::now();
    cout << "Dijkstra_with_optimize:\n";
    g.Dijkstra_withOptimize(0);    
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "Dijkstra_with_optimize runnning time: " << duration2 << "μs" << endl;

    auto start3 = chrono::high_resolution_clock::now();
    cout << "Floyd-Warshall:\n";
    g.FloydWarshall();
    auto end3 = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end3 - start3).count();
    cout << "FloydWarshall runnning time: " << duration3 << "μs" << endl;

    auto start4 = chrono::high_resolution_clock::now();
    cout << "Prim:\n";
    g.Prim();
    auto end4 = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(end4 - start4).count();
    cout << "Prim runnning time: " << duration4 << "μs" << endl;

    auto start5 = chrono::high_resolution_clock::now();
    cout << "Kruskal:\n";
    g.Kruskal();
    auto end5 = chrono::high_resolution_clock::now();
    auto duration5 = chrono::duration_cast<chrono::microseconds>(end5 - start5).count();
    cout << "Kruskal runnning time: " << duration5 << "μs" << endl;
    return 0;
}