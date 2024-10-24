//单源（从一个点出发），有向，带权，最短路问题
#include <iostream>
#include <cstring>
#define N 10010
using namespace std;
int n, m;
bool vis[N]; //该点最短路径是否已经被找到
int dis[N];
int g[N][N]; //g[1][2] 代表顶点 1 到顶点 2 的距离
void Dijkstra(){
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    dis[1] = 0; //顶点 1 到顶点 1 的距离为 0
    for(int i = 1; i <= n; i++){
        int min_w = -1;
        for(int j = 1; j <= n; j++){//找
            // min_w == -1 只控制第一次；此后均执行 dis[j] < dis[min_w]，找到最小权值
            if(!vis[j] && (min_w == -1) || (dis[j] < dis[min_w])){
                min_w = j;
            }
        }
        for(int j = 1; j <= n; j++){//更新
            dis[j] = min(dis[j], dis[min_w] + g[min_w][j]);
        }
        vis[min_w] = 1;
    }
    for(int i = 1; i <= n; i++){
        if(dis[i] == 0x3f3f3f3f) cout << -1 << endl;
        else cout << dis[i] << endl;
    }
}
int main(){
    memset(g, 0x3f3f3f3f, sizeof(g));
    cin >> n >> m;
    while(m--){
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);
    }
    Dijkstra();
    return 0;
}