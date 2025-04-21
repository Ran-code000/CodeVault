#include <iostream>
#include <unordered_map>
#include <string>
#include "Graph.h"

using namespace std;

unordered_map<string, int> mp = {}

int
main()
{
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; i++)
    {
        string su, sv;
        int w;
        graph.addEdge(mp[su], mp[sv], w);
    }
    cout << "\ndfs:\n";
    graph.dfs(1);
    cout << "\nbfs:\n";
    graph.bfs(1);
    cout << "\ndijkstra:\n";
    graph.dijkstra(1);
    return 0;
}