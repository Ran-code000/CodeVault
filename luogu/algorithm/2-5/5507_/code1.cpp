#include <iostream>
#include <map>
#include <queue>
//1379 八数码问题————一个状态衍生出 4 个状态
//5507 机关————一个状态衍生出 12 个状态
//暴搜，不做优化（核心思想 ———— 结构体存数组，数组变化模拟状态变化，数组拼接成数字储存状态，判断当前拼接好的数字（变化后的状态））
//拼接好的数字（状态）出现过（标记过） ———— 状态还原（now = temp）;
//拼接好的数字（状态）没出现过 （没标记过）———— 标记，入队列，状态还原（now = temp）;
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
using namespace std;
struct node{
    // x[13] 用数字保存状态
    int x[13], path[18] = {}, step;
}now, temp;//用两个变量，就不用像 1379 八数码难题一样再恢复状态
//拼接：数组 ———— 12 位数字
long long to_num(int *a){
    long long sum = 0;
    for(int i = 1; i <= 12; i++) sum = sum * 10 + a[i];
    return sum;
}
int a[13][5];
map<long long, int> vis;//标记为状态（ 12 位数字），用 map 映射标记（用 map 是最好的吗 ？）
queue<node> q;
void bfs(){
    long long temp_num;
    while(!q.empty()){
        temp = now = q.front();//用两个变量保证状态不需要恢复，简单
        q.pop();

        for(int i = 1; i <= 12; i++){
            //遍历改的哪一位
            now.x[a[i][now.x[i]]]++;//先转由联动引起转动的
            if(now.x[a[i][now.x[i]]] == 5) now.x[a[i][now.x[i]]] = 1;
            now.x[i]++; //再转本身需要转动的
            if(now.x[i] == 5) now.x[i] = 1;

            temp_num = to_num(now.x);//将转完后的数组拼接 ———— 数字（状态）
            //cout << temp_num << "\n"; 验证状态变化过程
            if(vis[temp_num]){
                //变化后的状态已存在
                now = temp;//恢复状态
                continue;
            }
            //变化后的状态不存在
            vis[temp_num] = 1;
            now.path[now.step++] = i;
            if(temp_num == 111111111111){
                cout << now.step << "\n";
                for(int j = 0; j < now.step; j++) cout << now.path[j] << " ";
                return;
            }
            /*cout << temp_num << ":" << now.step << ":";
            for(int j = 0; j < now.step; j++) cout << now.path[j] << " ";
            cout << "\n";*/
            q.push(now);
            now = temp;//将 now(现状态) 恢复为原状态（已用 temp 保存）
        }
    }
}
int main(){
    for(int i = 1; i <= 12; i++)
        for(int j = 0; j < 5; j++)
            cin >> a[i][j];//读入数据
    for(int i = 1; i <= 12; i++) now.x[i] = a[i][0];//纵向存数（只存了第一列）
    vis[to_num(now.x)] = 1;
    //cout << to_num(n.x); 验证基础函数
    q.push(now);
    bfs();
    return 0;
}