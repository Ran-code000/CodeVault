#include <iostream>
#include <queue>

using namespace std;
struct node{
    int x, y;
};
int n, m, dx[8] = {1, 1, 1, -1, -1, -1, 0, 0}, dy[8] = {1, -1, 0, 1, -1, 0, 1, -1}, ans = 0;
char a[101][101];
queue<node> q;
void bfs(int x, int y){
    q.push({x, y});
    a[x][y] = '.';

    while(!q.empty()){
        node t = q.front();
        q.pop();

        for(int i = 0; i < 8; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx < 1 || bx > n || by < 1 || by > m) continue;
            if(a[bx][by] == 'W'){
                a[bx][by] = '.';
                q.push({bx, by});
            }
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> a[i][j];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(a[i][j] == 'W'){
                bfs(i, j);
                ans++;
            }     
    cout << ans;
    return 0;
}