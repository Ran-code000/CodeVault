#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
struct node{
    int x, y;
};
int n, m, x, y, dx[8] = {1, 1, -1, -1, 2, 2, -2, -2}, dy[8] = {2, -2, 2, -2, 1, -1, 1, -1}, vis[401][401], steps = 0;
queue<node> q;

void bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();
        //steps++;
        for(int i = 0; i < 8; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx < 1 || bx > n || by < 1 || by > m) continue;
            if(vis[bx][by] == -1){
                //vis[bx][by] = steps;
                vis[bx][by] = vis[t.x][t.y] + 1;//上面的写法不对，bfs是按层渲染搜索，下一次的q.front()取的可能还是上一层的，不能直接steps++
                q.push({bx, by});
            }
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
    q.push({x, y});
    memset(vis, -1, sizeof(vis));
    vis[x][y] = 0;
    bfs();
    return 0;
}