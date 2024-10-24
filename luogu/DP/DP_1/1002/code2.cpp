#include <iostream>

using namespace std;
int n, m, xx, yy;
int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2}, dy[8] = {1, -1, 2, -2, 2, -2, 1, -1}, vis[22][22];
long long dp[22][22]; //答案可能很大，要开 long long
int main(){
    cin >> n >> m >> xx >> yy;
    //先平移再初始化
    n += 1, m += 1, xx += 1, yy += 1; //平移有效区域，后面不用特判 i > 0 和 j > 0 的情况
    vis[xx][yy] = 1; //初始化
    for(int i = 0; i < 8; i++){
        int bx = xx + dx[i], by = yy + dy[i];
        if(bx < 1 || bx > n || by < 1 || by > m) continue;
        vis[bx][by] = 1;
    }
    dp[1][1] = 1; //初始化
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(vis[i][j] || i == 1 && j == 1) continue; //跳过标记点和起点
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];      
        }
    }
    cout << dp[n][m];
    return 0;
}