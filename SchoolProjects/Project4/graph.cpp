#include "graph.h"
#include "stack.h"
#include <limits>

void Graph::addEdge(int u, int v, int w)
{
    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
}
void Graph::addVertex()
{
    VertexNum++;
}
int Graph::getVertexNum()
{
    return VertexNum;
}
std::vector<int> &Graph::dfs(int start, std::vector<int> &res)
{
    std::vector<bool> visit(VertexNum + 1, false);
    Stack<int> stk;

    stk.push(start);

    while (!stk.empty())
    {
        int t = stk.top();
        stk.pop();
        if (!visit[t])
        {
            visit[t] = true;
            res.push_back(t);
            for (auto i : adjList[t])
                if (!visit[i.first])
                    stk.push(i.first);
        }
    }

    return res;
}
std::vector<int> &Graph::bfs(int start, std::vector<int> &res)
{
    std::queue<int> q;
    std::vector<bool> visit(VertexNum + 1, false);

    q.push(start);

    while (!q.empty())
    {
        int t = q.front();
        q.pop();

        visit[t] = true;
        res.push_back(t);
        for (auto i : adjList[t])
        {
            if (!visit[i.first])
            {
                visit[i.first] = true;
                q.push(i.first);
            }
        }
    }
    return res;
}
std::vector<std::pair<int, int>> &Graph::dijkstra(int src, std::vector<std::pair<int, int>> &res)
{
    std::vector<bool> visit(VertexNum + 1, false);
    std::vector<int> distance(VertexNum + 1, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [nowMinDistance, currentNode] = pq.top();
        pq.pop();
        visit[currentNode] = true;

        for (auto [nextNode, currentDistance] : adjList[currentNode])
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
        res.push_back({i, distance[i]});
    }

    return res;
}

std::vector<std::vector<int>> &Graph::floyd(int src, std::vector<std::vector<int>> &res)
{
    // 初始化距离矩阵，将所有距离初始化为无穷大
    std::vector<std::vector<int>> distance(VertexNum + 1, std::vector<int>(VertexNum + 1, std::numeric_limits<int>::max()));

    // 对角线初始化为0（从每个节点到自身的距离是0）
    for (int i = 1; i <= VertexNum; i++)
    {
        distance[i][i] = 0;
    }

    // 初始化距离矩阵，根据邻接列表填充边的权重
    for (int i = 1; i <= VertexNum; i++)
    {
        for (auto [nextNode, weight] : adjList[i])
        {
            distance[i][nextNode] = weight;
        }
    }

    // 进行 Floyd-Warshall 算法的三重循环
    for (int k = 1; k <= VertexNum; k++)
    {
        for (int i = 1; i <= VertexNum; i++)
        {
            for (int j = 1; j <= VertexNum; j++)
            {
                if (distance[i][k] != std::numeric_limits<int>::max() && distance[k][j] != std::numeric_limits<int>::max() &&
                    distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= VertexNum; i++)
    {
        for (int j = 1; j <= VertexNum; j++)
        {
            if (distance[i][j] == std::numeric_limits<int>::max())
            {
                res[i][j] = -1;
            }
            else
            {
                res[i][j] = distance[i][j];
            }
        }
    }

    return res;
}