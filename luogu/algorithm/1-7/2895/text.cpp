#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int inf = 0x3f3f3f3f;
struct node{
    int x, y, time;
};
int n, vis1[302][302], vis2[302][302], dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
queue<node> q;

void Vis(int x, int y, int tt){
    for(int i = 0; i <  4; i++){
        int cx = x + dx[i], cy = y + dy[i];
        if(cx == -1 || cy == -1) continue;
        vis1[cx][cy] = min(vis1[cx][cy], tt);
    }
    vis1[x][y] = min(vis1[x][y], tt);
}

int bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();

        for(int i = 0; i < 4; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx == -1 || by == -1) continue;
            if(vis1[bx][by] == inf) return t.time + 1;
            if(!vis2[bx][by] && vis1[bx][by] > t.time + 1) {
                vis2[bx][by] = 1;
                q.push({bx, by, t.time + 1});
            }
        }
    }
    return -1;
}
int main(){
    cin >> n;
    memset(vis1, inf, sizeof(vis1));
    for(int i = 0; i < n; i++){
        int x, y, tt;
        cin >> x >> y >> tt;
        Vis(x, y, tt);
    }
    q.push({0, 0, 0});
    vis2[0][0] = 1;
    int min_time = bfs();
    cout << min_time;
    return 0;
}
