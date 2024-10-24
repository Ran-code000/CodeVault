/*
旅行商问题 (TSP)
旅行商问题（Traveling Salesman Problem, TSP）是一个经典的组合优化问题，目标是寻找一条最短的路径，
使得一位旅行商从一个城市出发，经过所有其他城市恰好一次后，回到原点。
该问题属于NP-困难问题，即没有已知的多项式时间算法可以解决所有情况。
*/
/*
数据范围 8 以内，暴力搜索
数据范围 12 以内，暴力搜索加剪枝
数据范围 20 以内，暴力搜索加状压剪枝
*/
#include <iostream>
#include <climits>
using namespace std;
struct node{
    double x, y;
    bool visit;
    int num;
}a[16];
int n;
double min_len = DBL_MAX, dp[16][33000];
void dfs(node p, int dep, int mark, double len){
    if(dep == n && min_len > len){
        min_len = len;
        return;
    }
    for(int i = 0; i < n; i++){
        if(a[i].visit) continue;
        int tmp = mark + 1 << i;
        if(dp[i][tmp] == 0 || dp[i][tmp] > dp[p.num][mark] + dis(a[i], p)){
            dp[i][tmp] = dp[p.num][mark] + dis(a[i], p);
            a[i].visit = 1;
            dfs(a[i], dep + 1, tmp, dis(a[i], p));
            a[i].visit = 0;
        }
        
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].visit = 0;
        a[i].num = i;
    }
    node t = {0, 0, 1};
    dfs(t, 0, 0, 0);
    return 0;
}