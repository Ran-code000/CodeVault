#include <iostream>
//#include <queue>
using namespace std;
/*struct node{
    int x, y, step = 0;
};*/
int n, m, x, y, ans = 0, vis[101][101], dx[] = {-1, 1, 0, 0, -1, -1, 1, 1}, dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
char a[101][101];
//queue<node> q;
void bfs(int x, int y){
    int step = 0, head = 0, tail = 0, q[10005][3];//用数组模拟队列；
    q[tail][0] = x;
    q[tail][1] = y;
    q[tail++][2] = step;
    while(head < tail){
        x = q[head][0];
        y = q[head][1];
        step = q[head++][2];

        for(int i = 0; i < 8; i++){
            int bx = x + dx[i], by = y + dy[i];
            if(bx < 0 || bx > n - 1 || by < 0 || by > m - 1) continue;
            if(!vis[bx][by] && a[bx][by] == '.'){
                vis[bx][by] = 1;
                q[tail][0] = bx;
                q[tail][1] = by;
                q[tail++][2] = step + 1;
            }
        }
    }
    ans = q[tail - 1][2];
}
int main(){
    cin >> m >> n >> y >> x;
    x = n - x;
    y--;
    vis[x][y] = 1;
    //q.push({n + 1 - y, x, 0});
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];
    bfs(x, y);
    cout << ans;
    return 0;
}