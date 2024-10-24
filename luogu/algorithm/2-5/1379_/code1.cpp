//广搜(单向广搜无优化)，优化见code2.cpp
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#define ans 123804765
using namespace std;
struct node{
    int x[10], step;
};
int n, min_step;

int dx[4] = {-3, 3, -1, 1};//上下左右
map<int, int> vis;//某个状态（数）是否走过（ 0 为没走过）
queue<node> q;
//将数组的数还原（拼成数）
int to_num(int a[]){
    int sum = 0;
    for(int i = 0; i < 9; i++) sum = sum * 10 + a[i];
    return sum;
}
int bfs(int now_pos){
    while(!q.empty()){
        node t = q.front();
        q.pop();
        
        //找起始位置（ 0 ）(注意要放在循环里面，每次都要从 0 开始往上下左右走)
        for(int i = 0; i < 9; i++){
            if(t.x[i] == 0){
                now_pos = i;
                break;
            }
        }
        for(int i = 0; i < 4; i++){
            //往上下左右走
            if(i == 0 && now_pos >= 3 || i == 1 && now_pos < 6 || i == 2 && (now_pos % 3 != 0) || i == 3 && (now_pos % 3 != 2)){
                //更新和还原时成对的
                swap(t.x[now_pos], t.x[now_pos + dx[i]]);//更新状态
                int temp = to_num(t.x);//保存更新后的状态
                if(temp == ans) return t.step + 1;
                if(!vis[temp]){
                    //没走过
                    vis[temp] = 1;
                    t.step++;//更新步数
                    q.push(t);
                    t.step--;//还原步数
                }
                swap(t.x[now_pos], t.x[now_pos + dx[i]]);//还原状态
            }
        }  
        
    }
    return -1;
}
int main(){
    cin >> n;
    if(n == ans){
        //特判
        cout << 0;
        return 0;
    }
    vis[n] = 1;//走过

    //初始化初状态，入队
    node start;
    start.x[0] = 0;//0 1 2 3 4 5 6 7 8（特殊情况）
    int pos = 8;
    while(n){
        //拆数，9位数字 ———— 用数组保存
        start.x[pos--] = n % 10;
        n /= 10;
    }
    //for(int i = 0; i < 9; i++) cout << start.x[i] << " "; //复杂问题输出验证一下
    start.step = 0;
    q.push(start);

    min_step = bfs(0);
    cout << min_step;
    return 0;
}