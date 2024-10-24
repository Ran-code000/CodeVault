#include <iostream>
#include <queue>

using namespace std;
struct node{
    int floor, steps;
};
int N, A, B;
int K[201], vis[201], dx[2] = {1, -1};
queue<node> q;

int bfs(){
    q.push({A, 0});
    while(!q.empty()){
        node t = q.front();
        q.pop();

        if(t.floor == B) return t.steps;//在for循环外面特判，可以包含如(A == B)的特殊情况，否则如果在for循环里面特判需要额外考虑A==B的情况
        for(int i = 0; i < 2; i++){
            int bfloor = t.floor + K[t.floor] * dx[i];
            if(bfloor >= 1 && bfloor <= N && !vis[bfloor]){
                vis[bfloor] = 1;
                q.push({bfloor, t.steps + 1});
            }
        }
    }
    return -1;
}
int main(){
    cin >> N >> A >> B;
    for(int i = 0; i < N; i++) cin >> K[i + 1];
    int min_step = bfs();
    cout << min_step;
    return 0;
}