#include <iostream>
#include <map>
#include <string>
#include <queue>
//暴搜 ———— 20 分
using namespace std;
struct node{
    string str;
    int step = 0, pos;
}now, temp;
map<string, bool> vis;
string ans = "111110111100*110000100000";
queue<node> q;
int n, dx[] = {-9, -3, 7, 11, -11, -7, 3, 9};
void bfs(){
    while(!q.empty()){
        temp = now = q.front();
        q.pop();
        for(int i = 0; i < 8; i++){
            if(now.pos + dx[i] < 0 || now.pos + dx[i] > 24) continue; //对行判断越界
            if((now.pos + 1) % 5 == 0 && i >= 0 && i <= 3) continue; //对最后一列（往右边跳）
            if(now.pos % 5 == 0 && i >= 4 && i < 8) continue; //对第一列（往左边跳）
            if((now.pos + 2) % 5 == 0 && (i == 1 || i == 2)) continue; //右数第二列
            if((now.pos - 1) % 5 == 0 && (i == 5 || i == 6)) continue; //左数第二列
            swap(now.str[now.pos], now.str[now.pos + dx[i]]);
            if(!vis[now.str]){
                if(now.step == 15){
                    cout << -1 << "\n";
                    return;
                }
                if(now.str == ans){
                    cout << now.step + 1 << "\n";
                    return;
                }
                vis[now.str] = 1;
                now.pos = now.pos + dx[i];
                now.step++;
                //cout << now.step << " " << now.pos << " " << now.str << "\n";
                q.push(now);
            }
            now = temp;
        }
    }
    cout << -1 << "\n";
    return;
}
int main(){
    cin >> n;

    string s;
    for(int i = 0; i < n; i++){
        //输入 n 组数据（逐个搜索即可）
        now.str = "";
        for(int j = 0; j < 5; j++){
            cin >> s;
            now.str += s;//用字符串拼接储存状态
        }
        now.step = 0;
        now.pos = now.str.find('*');
        vis[now.str] = 1;
        //cout << now.pos << " " << now.str << "\n";
        q.push(now);
        bfs();
        
        //每组数据的状态要还原（清空标记数组，清空队列）
        vis.clear();
        while(!q.empty()) q.pop();
    }
    
    return 0;
}