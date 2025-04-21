#include <iostream>
#include <unordered_map>
#include <string>
#include "Graph.h"

using namespace std;

unordered_map<int, string> provinces;

void init()
{
    provinces[1] = "Anhui (Ānhuī)";
    provinces[2] = "Beijing (Běijīng)";
    provinces[3] = "Chongqing (Chóngqìng)";
    provinces[4] = "Fujian (Fújiàn)";
    provinces[5] = "Gansu (Gānsù)";
    provinces[6] = "Guangdong (Guǎngdōng)";
    provinces[7] = "Guizhou (Guìzhōu)";
    provinces[8] = "Hainan (Hǎinán)";
    provinces[9] = "Hebei (Héběi)";
    provinces[10] = "Heilongjiang (Hēilóngjiāng)";
    provinces[11] = "Henan (Hénán)";
    provinces[12] = "Hubei (Húběi)";
    provinces[13] = "Hunan (Húnán)";
    provinces[14] = "Jiangsu (Jiāngsū)";
    provinces[15] = "Jiangxi (Jiāngxī)";
    provinces[16] = "Jilin (Jílín)";
    provinces[17] = "Liaoning (Liáoníng)";
    provinces[18] = "Ningxia (Níngxià)";
    provinces[19] = "Qinghai (Qīnghǎi)";
    provinces[20] = "Shaanxi (Shǎnxī)";
    provinces[21] = "Shandong (Shāndōng)";
    provinces[22] = "Shanghai (Shànghǎi)";
    provinces[23] = "Shanxi (Shānxī)";
    provinces[24] = "Sichuan (Sìchuān)";
    provinces[25] = "Tianjin (Tiānjīn)";
    provinces[26] = "Xinjiang (Xīnjiāng)";
    provinces[27] = "Xizang (Tibet) (Xīzàng)";
    provinces[28] = "Yunnan (Yúnnán)";
    provinces[29] = "Zhejiang (Zhèjiāng)";
    provinces[30] = "Guangxi (Guǎngxī)";
    provinces[31] = "Inner Mongolia (Neimenggu) (Neiménggǔ)";
    provinces[32] = "Hong Kong (Xiānggǎng)";
    provinces[33] = "Macau (Àomén)";

    for (const auto &province : provinces)
    {
        std::cout << "编号: " << province.first << " - " << province.second << std::endl;
    }
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; i++)
    {
        string su, sv;
        int w;
        graph.addEdge(provinces[su], provinces[sv], w);
    }
}

void test()
{
    cout << "\ndfs:\n";
    graph.dfs(1);
    cout << "\nbfs:\n";
    graph.bfs(1);
    cout << "\ndijkstra:\n";
    graph.dijkstra(1);
}

int main()
{
    init();
    test();
    return 0;
}