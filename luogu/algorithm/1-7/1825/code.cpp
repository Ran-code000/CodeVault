#include<iostream>
#include<queue>
using namespace std;
struct node{
    int x, y, time;
};
queue<node> q;
char a[301][301];
int vis[301][301], n, m, dx[4]={1, 0, -1, 0}, dy[4]={0, 1, 0, -1}, xx, yy;
void goto_another(int &x,int &y){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i][j] == a[x][y] && (i != x || j != y)){
                x=i;
                y=j;
                return;
            }
        }
    }
}
int bfs(){
    while(!q.empty())
    {
        node t = q.front();
        q.pop();

        if(a[t.x][t.y] == '=') return t.time;
        if(a[t.x][t.y] >= 'A' && a[t.x][t.y] <= 'Z') goto_another(t.x, t.y); //特判传输门，传输过程不耗费时间
        for(int i = 0; i < 4; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx < 1 || bx >  n || by < 1 || by > m || a[bx][by] == '#') continue;
            if(!vis[bx][by]){
                vis[bx][by] = 1;
                q.push({bx, by, t.time + 1});
            }
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            if(a[i][j] == '@'){
                xx = i;
                yy = j;
                q.push({xx,yy,0});
            }
        }
    }
    int min_time = bfs();
    cout << min_time;
    return 0;
}
