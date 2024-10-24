#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#define ans 123804765
using namespace std;
struct node{
    int x[10], step; 
};
int n, dx[] = {-3, 3, -1, 1}, min_step;
queue<node> q;
map<int, int> vis;
int to_num(int *a){
    int sum = 0;
    for(int i = 0; i < 9; i++) sum = sum * 10 + a[i];
    return sum;
}
int bfs(){
    int now_pos;
    while(!q.empty()){
        node t = q.front();
        q.pop();
        for(int i = 0; i < 9; i++){
            if(t.x[i] == 0){
                now_pos = i;
                break;
            }
        }
        for(int i = 0; i < 4; i++){
            if(i == 0 && now_pos >= 3 || i == 1 && now_pos < 6 || i == 2 && now_pos % 3 != 0 || i == 3 && (now_pos + 1) % 3 != 0){
                swap(t.x[now_pos], t.x[now_pos + dx[i]]);
                int temp = to_num(t.x);
                if(temp == ans) return t.step + 1;
                if(!vis[temp]){
                    vis[temp] = 1;
                    t.step++;
                    q.push(t);
                    t.step--;
                }
                swap(t.x[now_pos], t.x[now_pos + dx[i]]);
            }
        }
    }
    return -1;
}
int main(){
    cin >> n;
    if(n == ans){
        cout << 0;
        return 0;
    }
    vis[n] = 1;
    node start;
    int pos = 8;
    start.x[0] = 0;
    while(n){
        start.x[pos--] = n % 10;
        n /= 10; 
    }
    start.step = 0;
    q.push(start);
    min_step = bfs();
    cout << min_step;
    return 0;
}