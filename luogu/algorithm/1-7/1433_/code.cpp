#include <iostream>
#include <cmath>
#include <iomanip>
//完全深搜（无优化），50 ———— 优化见code2.cpp
using namespace std;
int n, vis[21];
double a[21][2], min_len = 1e9;
void dfs(int now, int dep, double len){
    if(dep == n){
        min_len = min(min_len, len);
        return;
    }
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        vis[i] = 1;
        double r1 = a[i][0] - a[now][0];
        double r2 = a[i][1] - a[now][1];
        double r = sqrt(r1 * r1 + r2 * r2);
        dfs(i, dep + 1, len + r);
        vis[i] = 0;
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
    dfs(0, 0, 0);
    cout << fixed << setprecision(2) << min_len;
    return 0;
}