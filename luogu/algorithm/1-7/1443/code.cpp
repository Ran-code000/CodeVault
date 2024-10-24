#include <iostream>
#include <queue>
#include <cstring>

//找最少步数，用广搜
struct node{
    int x, y;
};
using namespace std;
int n, m, x, y, a[401][401], vis[401][401];
int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
queue<node> q;

void bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();
        
        for(int k = 0; k < 8; k++){
        int bx = t.x + dx[k], by = t.y + dy[k];
        if(bx < 1 || bx > n || by < 1 || by > m || vis[bx][by] != -1) continue;
        vis[bx][by] = vis[t.x][t.y] + 1;
        q.push({bx, by});
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
    memset(vis, -1, sizeof(vis));
    vis[x][y] = 0;
    q.push({x, y});
    bfs();
    return 0;
}

