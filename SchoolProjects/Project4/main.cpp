#include <iostream>
#include <string>
#include "graph.h"
#include <unordered_map>
#include <algorithm>
#include <limits>

std::unordered_map<int, std::string> provinces;

bool COMP(const std::pair<int, std::string> &a, const std::pair<int, std::string> &b)
{
    return a.first < b.first;
}

int main()
{
    provinces[1] = "Anhui";
    provinces[2] = "Beijing";
    provinces[3] = "Chongqing";
    provinces[4] = "Fujian";
    provinces[5] = "Gansu";
    provinces[6] = "Guangdong";
    provinces[7] = "Guizhou";
    provinces[8] = "Hainan";
    provinces[9] = "Hebei";
    provinces[10] = "Heilongjiang";
    provinces[11] = "Henan";
    provinces[12] = "Hubei";
    provinces[13] = "Hunan";
    provinces[14] = "Jiangsu";
    provinces[15] = "Jiangxi";
    provinces[16] = "Jilin";
    provinces[17] = "Liaoning";
    provinces[18] = "Ningxia";
    provinces[19] = "Qinghai";
    provinces[20] = "Shaanxi";
    provinces[21] = "Shandong";
    provinces[22] = "Shanghai";
    provinces[23] = "Shanxi";
    provinces[24] = "Sichuan";
    provinces[25] = "Tianjin";
    provinces[26] = "Xinjiang";
    provinces[27] = "Xizang";
    provinces[28] = "Yunnan";
    provinces[29] = "Zhejiang";
    provinces[30] = "Guangxi";
    provinces[31] = "Inner Mongolia";
    provinces[32] = "Hong Kong";
    provinces[33] = "Macau";

    std::cout << "Sort the numbers of all provinces and cities in alphabetical order!\n";
    std::vector<std::pair<int, std::string>> temp(provinces.begin(), provinces.end());
    std::sort(temp.begin(), temp.end(), COMP);
    for (const auto &province : temp)
        std::cout << "编号: " << province.first << " - " << province.second << std::endl;

    Graph graph(33);
    std::cout << "\n---------------------------------------------------------------------------------\n";
    std::cout << "\n";
    std::cout << "Please input the graph\n";

    std::cout << "please input edges number: " << std::endl;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    std::cout << "\n---------------------------------------------------------------------------------\n";
    std::cout << "Input the way you want to travel: " << std::endl;
    std::cout << "( input DFS or BFS )\n"
              << std::endl;
    std::string way;
    std::cin >> way;
    std::cout << "\n---------------------------------------------------------------------------------\n";
    if (way == "DFS")
    {
        std::cout << "\nDFS:\n";
        std::vector<int> dfsResult;
        graph.dfs(1, dfsResult);
        for (size_t i = 0; i < dfsResult.size() - 1; i++)
        {
            std::cout << provinces[dfsResult[i]] << " ->";
        }
        std::cout << provinces[dfsResult[dfsResult.size() - 1]] << std::endl;
    }
    else if (way == "BFS")
    {
        std::cout << "\nBFS:\n";
        std::vector<int> bfsResult;
        graph.bfs(1, bfsResult);
        for (size_t i = 0; i < bfsResult.size() - 1; i++)
        {
            std::cout << provinces[bfsResult[i]] << " ->";
        }
        std::cout << provinces[bfsResult[bfsResult.size() - 1]] << std::endl;
    }

    std::cout << "\n---------------------------------------------------------------------------------\n";

    std::cout << "If you want to know the path of the unique city to other citys, please input the start city: ";
    std::string city;
    std::cin >> city;

    int id = 0;
    for (auto pair : provinces)
    {
        if (pair.second == city)
        {
            id = pair.first;
            break;
        }
    }
    std::cout << "\ndijkstra:\n";
    std::vector<std::pair<int, int>> dijkstraResult;
    graph.dijkstra(id, dijkstraResult);
    for (const auto &dijkstra : dijkstraResult)
    {
        std::cout << provinces[id] << " -> " << provinces[dijkstra.first] << ": " << dijkstra.second << std::endl;
    }

    std::cout << "\n---------------------------------------------------------------------------------\n";

    // std::cout << "If you want to know the path between any two citys, you can check the below table:\n";

    // std::cout << "\nfloyd:\n";
    // std::vector<std::vector<int>> floydResult(n + 1, std::vector<int>(n + 1, 0);
    // graph.floyd(id, floydResult);

    // for (size_t i = 1; i < floydResult.size(); i++)
    // {
    //     for (size_t j = 1; j < floydResult[i].size(); j++)
    //     {
    //         std::cout << floydResult[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}