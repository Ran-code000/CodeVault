#include <iostream>
#include <queue>
/*
为了确保找到最短路径， 因此需要 标记数组
BFS的目的是找到从起点到终点的最短路径。
在BFS中，一旦通过某条路径第一次访问到某个楼层，这条路径就保证了到达该楼层的最小步数。
再次访问同一楼层只会通过更长的路径，因为BFS是按层（步数）逐渐扩展的。所以，一旦某个楼层被访问，
再次访问不会找到更短的路径，只会浪费计算资源。


本题BFS比DFS更适用
BFS按层遍历，保证了一旦找到目的地，就是最短路径；
DFS是尽可能深地探索图的分支，不保证找到第一个解是最优解。DFS更适合寻找所有可能路径或者判断路径是否存在，不是寻最短路径
*/
using namespace std;
struct node{
    int floor, steps;
};
int N, A, B;
int vis[201], K[201], dx[2] = {1, -1};
queue<node> q;

int bfs(){
    while(!q.empty()){
        node t = q.front();//记录头元素
        q.pop();//弹出头元素

        if(t.floor == B) return t.steps;
        //列举方案数
        for(int i = 0; i < 2; i++){
            int bfloor = t.floor + K[t.floor] * dx[i];
            if(bfloor >= 1 && bfloor <= N && !vis[bfloor]){
                vis[bfloor] = 1;
                q.push({bfloor, t.steps + 1});//满足相应条件放进队列
            }
        }
    }
    return -1;
}
int main(){
    cin >> N >> A >> B;
    q.push({A, 0});
    for(int i = 0; i < N; i++) cin >> K[i + 1]; //调整索引下标
    int min_steps = bfs();
    cout << min_steps;
    return 0;
}