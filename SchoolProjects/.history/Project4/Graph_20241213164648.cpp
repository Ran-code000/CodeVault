#include <queue> // 包含 priority_queue

void Graph::dijkstra(int src)
{
    std::vector<int> distance(VertexNum + 1, std::numeric_limits<int>::max());
    std::vector<bool> visited(VertexNum + 1, false);

    distance[src] = 0;
    // 使用 priority_queue 来维护当前的最短路径
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (visited[node])
            continue; // 如果已访问过，则跳过
        visited[node] = true;

        for (auto [weight, neighbor] : adjList[node])
        {
            if (dist + weight < distance[neighbor])
            {
                distance[neighbor] = dist + weight;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= VertexNum; ++i)
    {
        if (distance[i] == std::numeric_limits<int>::max())
            std::cout << src << " -> " << i << " : INF" << std::endl;
        else
            std::cout << src << " -> " << i << " : " << distance[i] << std::endl;
    }
}