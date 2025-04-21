#include "Graph.h"
#include "stack.h"

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
void Graph::dijkstra()[

]