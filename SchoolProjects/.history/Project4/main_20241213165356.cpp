#include <iostream>
#include <string>
#include <unordered_map>
#include "graph.h"

std::unordered_map<int, std::string> provinces;
Graph graph(33);
int main()
{

    provinces[1] = "Anhui (Ānhuī)";
    provinces[2] = "Beijing (Běijīng)";
    provinces[3] = "Chongqing (Chóngqìng)";
    provinces[4] = "Fusian (Fújiàn)";
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
    for (int i = 0; i < 33; i++)
    {
        int u, v, w;
        graph.addEdge(u, v, w);
    }
    std::cout << "\ndfs:\n";
    graph.dfs(1);
    std::cout << "\nbfs:\n";
    graph.bfs(1);
    std::cout << "\ndijkstra:\n";
    graph.dijkstra(1);

    return 0;
}