#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
using namespace std;
enum class GraphType{ Undirected, Directed};
class Graph{
    int numVertices;
    vector<list<pair<int, int>>> adjList;
    GraphType type;
public:
    Graph(GraphType graphtype) : numVertices(0), type(graphtype){}
    void addVertex(){ adjList.resize(++numVertices);}
    void addEdge(int src, int dest, int weight = 1){
        if(type == GraphType::Directed) adjList[src].push_back({dest, weight});
        else if(type == GraphType::Undirected) adjList[src].push_back({dest, weight}), adjList[dest].push_back({src, weight});
    }
    void removeEdge(int src, int dest){
        adjList[src].erase(remove_if(adjList[src].begin(), adjList[src].end(), [dest](const auto& pair){ return pair.first == dest;}));
        if(type == GraphType::Undirected) adjList[dest].erase(remove_if(adjList[dest].begin(), adjList[dest].end(), [src](const auto& pair){ return pair.first == src;}));
    }
    // ... (Other methods like addVertex, removeVertex, getNeighbors, DFS, BFS, Dijkstra, FroydWarshall, Prim, Kruskal, etc.)
    //add methods;
    //Topological Sort: This is applied to a directed graph to determine a valid order of vertices where each vertex comes before its neighbors. 
    //If a cycle exists, the sort fails.
    void Topological_sort(){
        vector<int> inDegree(numVertices, 0);
        for(const auto& list : adjList)
            for(const auto& pair : list)
                inDegree[pair.first]++;
        queue<int> _queue;
        for(int i = 0; i < numVertices; i++) if(inDegree[i] == 0) _queue.push(i);
        vector<int> sortedOrder;
        while(!_queue.empty()){
            int currentVertex = _queue.front();
            _queue.pop();
            sortedOrder.push_back(currentVertex);
            for(const auto& pair : adjList[currentVertex]){
                inDegree[pair.first]--;
                if(inDegree[pair.first] == 0) _queue.push(pair.first);
            }
        }
        //If a cycle exists
        if(sortedOrder.size() != numVertices){ cout << "Graph has at least one cycle." << endl; return;}
        for(int v : sortedOrder) cout << v << " ";
        cout << endl;
    }
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
int main() {
    // Example usage for Directed Graph
    // must to be for Directed Graph
    Graph g(GraphType::Directed);
    g.addVertex();
    g.addVertex(); // 添加第二个顶点
    g.addVertex(); // 添加第三个顶点
    g.addVertex(); // 添加第四个顶点
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.printGraph();
    g.drawGraph();
    g.Topological_sort();

    return 0;
}