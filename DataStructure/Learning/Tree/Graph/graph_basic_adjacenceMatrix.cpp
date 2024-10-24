#include <iostream>
#include <vector>
using namespace std;
class Graph{
    int numVertices;
    vector<vector<int>> adjMatrix;
public:
    Graph(int vertices) : numVertices(vertices), adjMatrix(vertices, vector<int>(vertices, 0)){}
    void addEdge(int src, int dest){
        if(src >= 0 && src < numVertices && dest >= 0 && dest < numVertices){
            adjMatrix[src][dest] = 1;
            adjMatrix[dest][src] = 1;
        }
    }
    void printGraph(){
        cout << "  ";
        for(int i = 0; i < numVertices; i++) cout << i << " ";
        cout << endl;        
        for(int i = 0; i < numVertices; i++){
            cout << i << " ";
            for(int j = 0; j < numVertices; j++){
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
            
        cout << endl;
    }
    bool hasEdge(int src, int dest){ return adjMatrix[src][dest] == 1;}
};
int main() {
    // 创建一个有 4 个顶点的图
    Graph g(4);
    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    // 打印图
    g.printGraph();
    cout << "(2, 1):" << g.hasEdge(2, 1) << endl;
    cout << "(1, 1):" << g.hasEdge(1, 1) << endl;
    return 0;
}