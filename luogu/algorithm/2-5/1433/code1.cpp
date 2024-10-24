#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int n, vis[16];
double x[16], y[16], min_len, dp[16][1 << 16];
double dfs(int dep, double sum_len, int now_pos, double now_len, int path){
    if(dep == n) return now_len;
    if(dp[now_pos][path]) return dp[now_pos][path] + now_len;
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        vis[i] = 1;
        double r1 = x[i] - x[now_pos];
        double r2 = y[i] - y[now_pos];
        double r = sqrt(r1 * r1 + r2 * r2);
        sum_len = min(sum_len, bfs(dep + 1, 1e9, i, now_len + r, path | 1 << i));
        vis[i] = 0;
    }
    dp[now_pos][path] = sum_len - now_len;
    return sum_len;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    x[0] = 0;
    y[0] = 0;
    vis[0] = 1;
    min_len = dfs(0, 1e9, 0, 0, 0);
    cout << fixed << setprecision(2) << min_len;
    return 0;
}