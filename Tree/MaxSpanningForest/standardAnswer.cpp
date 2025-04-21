#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

class Graph
{
    int vertexNum;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int n) : vertexNum(n), adj(n) {}

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs(int i, vector<bool> &visit, vector<int> &res)
    {
        visit[i] = true;
        res.push_back(i);

        for (auto j : adj[i])
        {
            if (!visit[j.first])
            {
                dfs(j.first, visit, res);
            }
        }
    }

    int maxSpanningTree(int i)
    {
        vector<int> weight(vertexNum, numeric_limits<int>::min());
        vector<bool> visit(vertexNum, false);

        priority_queue<pair<int, int>> pq;

        pq.push({0, i});
        weight[i] = 0;

        int mstWeight = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            int w = pq.top().first; 
            pq.pop();

            if (visit[u])
                continue;
            visit[u] = true;
            mstWeight += w;

            for (auto &edge : adj[u])
            {
                int v = edge.first;
                int weight_uv = edge.second;
                if (!visit[v] && weight[v] < weight_uv)
                {
                    weight[v] = weight_uv;
                    pq.push({weight_uv, v});
                }
            }
        }

        return mstWeight;
    }

    vector<pair<int, int>> GetAdj(int i)
    {
        return adj[i];
    }
};

int main()
{
    int N;
    cin >> N;

    while (N--)
    {
        int n, m;
        cin >> n >> m;

        Graph g(n);

        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g.addEdge(u, v, w);
        }

        vector<bool> visit(n, false);
        int totalSum = 0;

        for (int i = 0; i < n; i++)
        {
            if (!visit[i])
            {
                vector<int> res;
                g.dfs(i, visit, res);

                Graph subGraph(res.size());
                for (int j = 0; j < res.size(); j++)
                {
                    int u = res[j];
                    for (auto edge : g.GetAdj(u))
                    {
                        int v = edge.first, w = edge.second;
                        if (find(res.begin(), res.end(), v) != res.end())
                        {
                            //映射
                            subGraph.addEdge(j, find(res.begin(), res.end(), v) - res.begin(), w);
                        }
                    }
                }

                totalSum += subGraph.maxSpanningTree(0);
            }
        }
        cout << totalSum << endl;
    }

    return 0;
}