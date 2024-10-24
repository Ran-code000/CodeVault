#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

//深搜处理，但加多了条件限制
using namespace std;
const int inf = 0x3f3f3f3f;//必须要0x3f3f3f3f才行， 0x3f3f3f等等都不行
//0x3f3f3f3f 足够大，可以代表一个很大的数，但又不至于大到导致整数溢出（比如 0x7fffffff 是 int 的最大值）
struct node{
    int x, y, time;
};
int n, vis1[302][302], vis2[302][302], dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
queue<node> q;
void Vis(int x, int y, int tt){
    for(int i = 0; i <  4; i++){
        int cx = x + dx[i], cy = y + dy[i];
        if(cx == -1 || cy == -1) continue;//边界判断
        vis1[cx][cy] = min(vis1[cx][cy], tt);//取第一次标记的时间（较小）
    }
    vis1[x][y] = min(vis1[x][y], tt);
}
int bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();

        //判断时间限制是否符合条件（陨石的时间和我的步数/时间比较）
        for(int i = 0; i < 4; i++){
            int bx = t.x + dx[i], by = t.y + dy[i];
            if(bx == -1 || by == -1) continue;
            if(vis1[bx][by] == inf) return t.time + 1;//标记的时候已经将四周标记过， 因此只需判断当前位置是否永远不会出现陨石
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
    //注意先对第一个元素进行处理
    q.push({0, 0, 0});//将第一个元素放进队列里
    vis2[0][0] = 1;//标记第一个元素
    int min_time = bfs();
    cout << min_time;
    return 0;
}