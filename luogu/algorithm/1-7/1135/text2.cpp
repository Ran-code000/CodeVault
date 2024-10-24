#include <iostream>
#include <queue>

using namespace std;
struct node{
    int floor, cnt;
};
int N, A, B, dx[2] = {1, -1}, dy[201], vis[201];
queue<node> q;
int bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();
        
        if(t.floor == B) return t.cnt;
        for(int i = 0; i < 2; i++){
            int nextfloor = t.floor + dy[t.floor] * dx[i];
            if(nextfloor < 1 || nextfloor > N) continue;
            if(!vis[nextfloor]){
                vis[nextfloor] = 1;
                q.push({nextfloor, t.cnt + 1});
            }
        }
    }
    return -1;
}
int main(){
    cin >> N >> A >> B;
    for(int i = 1; i <= N; i++){
        cin >> dy[i];
    }
    q.push({A, 0});
    int min_steps = bfs();
    cout << min_steps;
    return 0;
}