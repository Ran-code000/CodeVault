//不同于 1379 八数码问题 的优化 ———— 用双向 bfs（不存在正反，不需要输出轨迹）
//5507 机关 的优化不宜用双向 bfs 
//(因为本题存在正反（起点正着加，终点倒着减），且需要输出轨迹（只能找到从起点开始的轨迹，找不到从终点开始的轨迹）)

//启发式搜索 ———— 不用普通队列了（queue），用优先队列（priority_queue<int> q）
/*
3 3 7 2 6
3 1 4 5 3
3 1 2 6 4
3 1 10 3 5
3 2 8 3 6
3 7 9 2 1
1 1 2 3 4
1 3 11 10 12
1 8 6 7 4
1 9 9 8 8
1 12 10 12 12
1 7 8 9 10
*/
#include <iostream>
#include <map>
#include <queue>

using namespace std;
struct node{
    int x[13], step = 0, path[18] = {};
    bool operator()(node a, node b){
        //这个比较逻辑用于建立最小堆，以找出成本最低的节点。
        int suma = 0, sumb = 0;//a, b 节点距离终点需要走的步数的和
        for(int i = 1; i <= 12; i++){
            suma += (5 - a.x[i]) % 4; 
            sumb += (5 - b.x[i]) % 4;
        }
        //节点 a 的总成本高于节点 b，则返回 true，否则返回 false
        return suma / 2 + a.step > sumb / 2 + b.step; //距离目标多少步 + 当前已走多少步；
        // 除 2 （ /2 ） 是因为转一次旋钮实际改变状态的两位（一共 12 位）（理解为走两步）
        //1 + 2 和 2 + 2 优先选 2 + 2； 1 + 4 和 2 + 2 优先选 2 + 2；
    }//排序回调函数 ———— 两个小括号，后面的小括号填参数
}now, temp;
int a[13][5];
//map<long long, int> vis;
int vis[20000000];//开一个 2000 0000 的桶
priority_queue<node, vector<node>, node> q;
/*long long to_num(int *x){
    long long sum = 0;
    for(int i = 1; i <= 12; i++) sum = sum * 10 + x[i];//十进制
    for(int i = 1; i <= 12; i++) sum = sum * 4 + x[i];
    return sum; 
}*/
int to_num(int *x){
    int sum = 0;
    for(int i = 1; i <= 12; i++) sum = sum * 4 + (x[i] - 1);//四进制
    return sum;
}
void bfs(){
    long long temp_num;
    int c[13] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//注意编号从1到12，索引 0 未使用
    while(!q.empty()){
        temp = now = q.top();//优先队列取 top 不是 front
        q.pop();

        for(int i = 1; i <= 12; i++){
            now.x[a[i][now.x[i]]]++;
            if(now.x[a[i][now.x[i]]] == 5) now.x[a[i][now.x[i]]] = 1;
            now.x[i]++;
            if(now.x[i] == 5) now.x[i] = 1;
            temp_num = to_num(now.x);
            now.path[now.step++] = i;
            if(!vis[temp_num]){
                //90分，因为 map 的查找（二分查找）———— log n 的时间复杂度
                //优化 ———— 桶标记 （不同于八数码问题 ———— 9 位且每位 9 个数耗费空间大）
                //———— 本题虽为 12 位数字，但每位最多为 4 ———— 最多到 2000 0000
                //经验：内存限制 512 MB ———— 4000 0000；内存限制 128 MB ———— 1000 0000
                vis[temp_num] = 1;
                //if(temp_num == 111111111111) 改为四进制
                if(temp_num == to_num(c)){
                    cout << now.step << "\n";
                    for(int j = 0; j < now.step; j++) cout << now.path[j] << " ";
                    return;
                }
                q.push(now);
            }
            now = temp;
        }
    }
}
int main(){
    for(int i = 1; i <= 12; i++)
        for(int j = 0; j < 5; j++)
            cin >> a[i][j];
    for(int i = 1; i <= 12; i++) now.x[i] = a[i][0];
    vis[to_num(now.x)] = 1;
    q.push(now);
    bfs();
    return 0;
}

