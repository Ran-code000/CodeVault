//双向广搜（已知初始和目标状态）
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
struct node{
    int x[10], step, type; 
    //该状态拆分后的数组，到达该状态的步数，该状态的类型（从起点还是终点）
};
int ans = 123804765;
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
                if(temp == ans && t.step < 1000) return t.step + 1;//从起点开始找的
                if(vis[temp] == 0){
                    //没走过
                    //vis[temp] = 1;//不能只标记为 1，可以同时用来记录步数，因为需要通过步数来判断是从起点来的还是终点来的
                    //用vis[temp] 记录步数可以理解为记录了这个状态的步数性质，一旦标记就不再改变，此后只判断（双向bfs必须用vis标）
                    //单向 bfs 可以用 vis 纯标记，也可以用来记录步数
                    vis[temp] = ++t.step;
                    q.push(t);
                    t.step--;
                }else if(vis[temp] != -1 && ((t.type && vis[temp] < 1000) || !t.type && vis[temp] > 1000)){
                    //不能返回起点，两种情况
                    //从起点出发的线（vis[step] < 1000）碰到从终点演变而来的情况；
                    //从终点出发的线（vis[step] > 1000）碰到从起点演变而来的情况；
                    return t.step + 1 + vis[temp] - 1000;
                    //vis[temp] 不同于 t.step : 
                    //vis[temp] 为第一次到达这个状态的步数（要么 < 1000 为起点来的，要么 > 1000 为终点来的）
                    //当没走过这个状态时 vis[temp] == t.step + 1，此时已经固定不能再更新 vis[temp]
                    //当已走过这个状态，只能判断 t.type 即这个状态从何更新而来，
                    //因为此时的 t.step 是当前点的（当前准备走的下一个点是已标记为不能走的点），所以此时 vis[temp] != t.step + 1;
                    //所以条件不能错误的写为 vis[temp] != -1 && ((t.type && t.step < 1000) || !t.type && t.step > 1000)
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
    vis[n] = -1;//起点特殊标记来区分，不能只标记为走过（1）

    node start, endd;
    int pos = 8;
    start.x[0] = 0;
    while(n){
        start.x[pos--] = n % 10;
        n /= 10; 
    }
    start.step = 0, start.type = 0;
    q.push(start);

    pos = 8;
    endd.x[0] = 0;
    while(ans){
        endd.x[pos--] = ans % 10;
        ans /= 10; 
    }
    endd.step = 1000, endd.type = 1;
    //最后 start.step + endd.step - 1000 即可
    q.push(endd);

    min_step = bfs();
    cout << min_step;
    return 0;
}