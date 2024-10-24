#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
//广搜 + 优先队列优化 + 剪枝优化 + 双向 bfs 优化
//优先队列优化 ———— 20 分 248ms
using namespace std;
string ans = "111110111100*110000100000";
struct node{
    string str;
    int step = 0, pos, type;
    //回调函数
    bool operator ()(node a, node b){
        int sa = 0, sb = 0;
        for(int i = 0; i < 25; i++){
            if(a.str[i] != ans[i]) sa++; //到 a 节点（状态）还有几个位置不同（至少还要走几步）
            if(b.str[i] != ans[i]) sb++; //到 b 节点（状态）还有几个位置不同（至少还要走几步）
        }
        return a.step + sa > b.step + sb; //至少要走的步数 + 已走过的步数
        //按最小堆排列，步数小的（更好的方案）优先出列
    }
}now, temp, endd;
map<string, bool> vis;
//queue<node> q;
priority_queue<node, vector<node>, node> q;//优先队列优化
int n, dx[] = {-9, -3, 7, 11, -11, -7, 3, 9};
void bfs(){
    while(!q.empty()){
        //temp = now = q.front();
        temp = now = q.top();
        q.pop();
        for(int i = 0; i < 8; i++){
            //越界判断 ————— 二维空间压缩到一维空间
            if(now.pos + dx[i] < 0 || now.pos + dx[i] > 24) continue; //对行判断越界
            if((now.pos + 1) % 5 == 0 && i >= 0 && i <= 3) continue; //对最后一列（往右边跳）
            if(now.pos % 5 == 0 && i >= 4 && i < 8) continue; //对第一列（往左边跳）
            if((now.pos + 2) % 5 == 0 && (i == 1 || i == 2)) continue; //右数第二列
            if((now.pos - 1) % 5 == 0 && (i == 5 || i == 6)) continue; //左数第二列
            swap(now.str[now.pos], now.str[now.pos + dx[i]]);//更新状态（字符串保存）

            //剪枝优化 ———— 127ms
            int num = 0;
            for(int i = 0; i < 25; i++)
                if(now.str[i] != ans[i]) num++; //还有多少的点不一样（至少还要走多少步）
            if(now.step + num > 15){
                now = temp;
                continue;
            }

            if(!vis[now.str]){
                if(now.step == 15){
                    cout << -1 << "\n";
                    return;
                }
                if(now.str == ans){
                    cout << now.step + 1 << "\n";
                    return;
                }
                vis[now.str] = ++now.step;
                now.pos = now.pos + dx[i];
                //cout << now.step << " " << now.pos << " " << now.str << "\n";
                q.push(now);
            }

            //双向 bfs 优化 ———— 168ms
            if(vis[now.str] != -1 && (vis[now.str] > 1000 && !now.type || vis[now.str] < 1000 && now.type)){
                cout << now.step + 1 + vis[now.str] - 1000 << "\n";
                return;
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
        now.step = 0, now.type = 0;
        now.pos = now.str.find('*');
        vis[now.str] = -1;

        //双向 bfs ———— 初始化并入队目标状态
        endd.step = 1000, endd.type = 1;
        endd.pos = endd.str.find('*');
        endd.str = ans;
        //cout << now.pos << " " << now.str << "\n";
        q.push(now);
        q.push(endd);
        bfs();
        
        //每组数据的状态要还原（清空标记数组，清空队列）
        vis.clear();
        while(!q.empty()) q.pop();
    }
    
    return 0;
}