#include <iostream>

using namespace std;
int N, M, T, x1, y1, x2, y2, a[6][6], vis[6][6], dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1}, ans = 0;

void dfs(int x, int y){
    if(x == x2 && y == y2){
        ans++;
        return;
    }
    for(int i = 0; i < 4; i++){
        int bx = x + dx[i], by = y + dy[i];
        if(bx < 1 || bx > N || by < 1 || by > M) continue;
        if(!vis[bx][by]){
            vis[bx][by] = 1;
            dfs(bx, by);
            vis[bx][by] = 0;
        }
    }
}
int main(){
    cin >> N >> M >> T >> x1 >> y1 >> x2 >> y2;
    vis[x1][y1] = 1;
    for(int i = 0; i < T; i++){
        int x, y; 
        cin >> x >> y;
        vis[x][y] = 1;
    }
    dfs(x1, y1);
    cout << ans;
    return 0;
}