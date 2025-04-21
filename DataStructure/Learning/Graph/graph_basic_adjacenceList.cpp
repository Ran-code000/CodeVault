#include <iostream>
#include <vector>
#include <list>
using namespace std;
//邻接表构建无向图
class Graph{
    int numVertices;
    vector<list<int>> adjList;// 使用 list 是为了高效处理邻接表的动态调整操作（如插入和删除边），同时避免了频繁的内存重新分配。
public:
    Graph(int vectices) : numVertices(vectices){
        adjList.resize(numVertices);
    }
    void addEdge(int src, int dest){
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }
    void printGraph(){
        for(int i = 0; i < numVertices; i++){
            cout << "Vertex " << i << " has neighbors: ";
            for(int neighbors : adjList[i]) cout << neighbors << " ";
            cout << endl;
        }
    }
};
int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.printGraph();

    return 0;
}
// 1. 高效的插入和删除操作
//  list 是一个双向链表，在链表的任意位置进行插入或删除元素的时间复杂度是 O(1)，因为它不涉及内存块的重新分配或移动其他元素。
//  这对于图的邻接表表示尤其有用，特别是当频繁添加或删除边时。
//  例如，addEdge() 函数中调用了 push_back() 向链表末尾添加元素，list 允许在常数时间内完成这个操作，而不会像 vector 那样可能需要重新分配内存。

// 2. 不需要随机访问
// 在图的邻接表表示中，通常只需要遍历一个顶点的邻接边，而不是随机访问某个特定的邻接顶点。list 的顺序访问比 vector 更加合适，
// 因为不需要直接访问指定位置的元素（list 不支持快速的随机访问，时间复杂度为 O(n)，而 vector 的随机访问是 O(1)）。

// 3. 存储效率
// list 是链式结构，内存分配是非连续的，这意味着当频繁增加或删除元素时，它不会像 vector 一样有额外的开销
// 比如当 vector 空间不足时，它需要重新分配更大的内存块并复制已有数据。
// 对于稀疏图或需要频繁动态调整边的图结构来说，list 的这种特点在性能和内存利用上可能更有优势。

// 4. 无向图的双向边处理
// 对于无向图，每条边都需要在邻接表中存储两次（src -> dest 和 dest -> src）。
// 由于 list 的插入操作非常高效，因此在处理双向边时，它的性能更加合适。
