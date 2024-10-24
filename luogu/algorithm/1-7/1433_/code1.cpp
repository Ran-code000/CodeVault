#include <iostream>
#include <iomanip>
#include <cmath>
//加入记忆化搜索
using namespace std;
int n, vis[21];
double a[21][2], dp[21][1 << 16], min_len;
double dfs(int now, int dep, double len, int path){
    double ans = 1e9;
    if(dep == n) return len;
    //dp[now][path] 给出的是从 now 开始，完成所有未访问节点的访问并最终返回的最优路径长度
    if(dp[now][path]) return len + dp[now][path];
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        vis[i] = 1;
        double r1 = a[i][0] - a[now][0];
        double r2 = a[i][1] - a[now][1];
        double r = sqrt(r1 * r1 + r2 * r2);
        ans = min(ans, dfs(i, dep + 1, len + r, path | 1 << i));
        vis[i] = 0;
    }
    dp[now][path] = ans - len;
    return ans;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
    min_len = dfs(0, 0, 0, 0);
    cout << fixed << setprecision(2) << min_len;
    return 0;
}