#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
int n, vis[16];
double dp[16][1 << 16], x[16], y[16], min_len;
double dfs(int dep, int now_pos, double now_len, double sum_len, int path){
    if(dep == n) return now_len;
    if(dp[now_pos][path]) return dp[now_pos][path] + now_len;
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        vis[i] = 1;
        double r1 = x[i] - x[now_pos];
        double r2 = y[i] - y[now_pos];
        double r = sqrt(r1 * r1 + r2 * r2);
        sum_len = min(sum_len, dfs(dep + 1, i, now_len + r, 1e9, path | 1 << i));
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
    min_len = dfs(0, 0, 0, 1e9, 0);
    cout << fixed << setprecision(2) << min_len;
    return 0;
}