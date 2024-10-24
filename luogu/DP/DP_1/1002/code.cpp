#include <iostream>

//搜索会WA， 时间复杂度太高
using namespace std;
int n, m, x2, y2, dx[8] = {2, 2, 1, 1, -1, -1, -2, -2}, dy[8] = {1, -1, 2, -2, 2, -2, 1, -1}, a[22][22], vis[22][22], cnt = 0;
int dxx[2] = {0, 1}, dyy[2] = {1, 0};
void dfs(int x, int y){
    if(x == n && y == m){
        cnt++;
        return;
    }
    for(int i = 0; i < 2; i++){
        int ax = x + dxx[i], ay = y + dyy[i];
        if(ax < 0 || ax > n || ay < 0 || ay > m) continue;
        if(!vis[ax][ay]){
            vis[ax][ay] = 1;
            dfs(ax, ay);
            vis[ax][ay] = 0;
        }
    }
}
int main(){
    cin >> n >> m >> x2 >> y2;
    for(int i = 0; i < 8; i++){
        int bx = x2 + dx[i], by = y2 + dy[i];
        if(bx < 0 || bx > n || by < 0 || by > m) continue;
        vis[bx][by] = 1;
    }
    vis[0][0] = 1;
    vis[x2][y2] = 1;
    dfs(0, 0);
    cout << cnt;
    return 0;
}