#include "graph.h"
#include "stack.h"
#include <limits>

void Graph::addEdge(int u, int v, int w)
{
    adjList[u].push_back({v, w});
}
void Graph::addVertex()
{
    VertexNum++;
}
int Graph::getVertexNum()
{
    return VertexNum;
}
void Graph::dfs(int start)
{
    std::vector<bool> visit(VertexNum + 1, false);
    stack<int> stk;

    stk.push(start);

    while (!stk.empty())
    {
        int t = stk.top();
        stk.pop();
        if (!visit[t])
        {
            visit[t] = true;
            cout << t << " ";
            for (auto i : adjList[t])
                if (!visit[i.first])
                    stk.push(i.first);
        }
    }
}
void Graph::bfs(int start)
{
    std::queue<int> q;
    std::vector<bool> visit(VertexNum + 1, false);

    q.push(start);

    while (!q.empty())
    {
        int t = q.front();
        q.pop();

        visit[t] = true;
        cout << t << " ";
        for (auto i : adjList[t])
            if (!visit[i.first])
                q.push(i.first);
    }
}
void Graph::dijkstra(int src)
{
    std::vector<bool> visit(VertexNum + 1, false);
    std::vector<int> distance(VertexNum + 1, std::numeric_limits<int>::max());
    std::queue<pair<int, int>> pq;

    distance[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [nowMinDistance, currentNode] = pq.front();
        pq.pop();

        for (auto [currentDistance, nextNode] : adjList[currentNode])
        {
            if (!visit[nextNode] && nowMinDistance + currentDistance < distance[nextNode])
            {
                distance[nextNode] = nowMinDistance + currentDistance;
                pq.push({distance[nextNode], nextNode});
            }
        }
    }

    for (int i = 1; i <= VertexNum; i++)
    {
        cout << src << " -> " << i << " : " << distance[i] << endl;
    }
}