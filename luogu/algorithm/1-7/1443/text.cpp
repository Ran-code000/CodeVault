#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
struct node{
    int x, y;
};
int n, m, x, y;
int vis[401][401];
int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
queue<node> q;

void bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();
        for(int i = 0; i < 8; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx < 1 || bx > n || by < 1 || by > m || vis[bx][by] != -1) continue;
            q.push({bx, by});
            vis[bx][by] = vis[t.x][t.y] + 1;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cout << vis[i][j] << " ";
        }
        cout << "\n";
    }
}
int main(){
    cin >> n >> m >> x >> y;
    memset(vis, -1 , sizeof(vis));
    vis[x][y] = 0;
    q.push({x, y});
    bfs();
    return 0;
}