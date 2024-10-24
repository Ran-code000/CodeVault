#include <iostream>
#include <queue>

using namespace std;
int n, m, f[1001][1001], ans;
char a[1001][1001];
struct node{
    int x, y;
};
queue<node> q;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
void bfs(int x,int y){
    q.push({x, y});
    a[x][y] == '0';
    while(!q.empty()){
        node t = q.front();
        q.pop();
        for(int i = 0; i < 4; i++){
            int xx = t.x + dx[i], yy = t.y + dy[i];
            if(x >= 1 && x <= n && y >= 1 && y <= m && a[xx][yy] != '0'){
                q.push({xx, yy});
                a[xx][yy] = '0';
            }
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; i++){
            if(a[i][j] !=  '0'){
                ans++;
                bfs(i, j);
            }
        }
    }
    cout << ans;
    return 0;
}