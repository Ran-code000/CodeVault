#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
struct node{int num[10], step, type;};
queue<node> q;
unordered_map<int, int> vis;
int n, min_step, dx[4] = {-3, 3, -1, 1}, ans = 123804765;
inline int to_num(int *a){int sum = 0; for(int i = 0; i < 9; i++) sum = sum * 10 + a[i]; return sum;}
int bfs(){
    while(!q.empty()){
        int id;
        node temp = q.front();
        q.pop();
        for(int i = 0; i < 9; i++) if(temp.num[i] == 0) {id = i; break;}
        for(int i = 0; i < 4; i++){
            if(i == 0 && id >= 3 || i == 1 && id <= 5 || i == 2 && id % 3 != 0 || i == 3 && (i + 1) % 3 != 0){
                node a = temp;
                swap(a.num[id], a.num[id + dx[i]]);
                int now_num = to_num(a.num);
                if(now_num == 123804765 && a.step < 1000) return a.step + 1;
                if(!vis[now_num]) {vis[now_num] = ++a.step; q.push(a);}
                else if(vis[now_num] != -1 && (a.type && vis[now_num] < 1000 || !a.type && vis[now_num] > 1000)) return vis[now_num] + a.step + 1 - 1000;
            }

        }
    }
    return -1;
}
int main(){
    cin >> n;
    if(n == 123804765){cout << 0; return 0;}
    vis[n] = -1;

    node now, des;
    now.num[0] = 0;
    int pos = 8; 
    while(n){now.num[pos--] = n % 10; n /= 10;}
    now.step = 0, now.type = 0;
    q.push(now);
    
    des.num[0] = 0;
    pos = 8; 
    while(ans){des.num[pos--] = ans % 10; ans /= 10;}
    des.step = 1000, des.type = 1;
    q.push(des);

    min_step = bfs();
    cout << min_step;
    return 0;
}