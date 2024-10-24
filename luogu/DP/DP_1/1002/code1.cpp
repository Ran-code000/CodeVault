#include <iostream>

using namespace std;
int n, m, xx, yy;
int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2}, dy[8] = {1, -1, 2, -2, 2, -2, 1, -1}, vis[21][21];
long long dp[21][21]; //答案可能很大，要开 long long
int main(){
    cin >> n >> m >> xx >> yy;
    vis[xx][yy] = 1; //注意需要初始化！！！
    for(int i = 0; i < 8; i++){
        int bx = xx + dx[i], by = yy + dy[i];
        if(bx < 0 || bx > n || by < 0 || by > m) continue;
        vis[bx][by] = 1;
    }
    dp[0][0] = 1; //初始化起始点
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(vis[i][j] || i == 0 && j == 0) continue; //跳过标记点和起点
            //由于起点是(0, 0) 当遇到 i - 1 和 j - 1 时需要边界特判(可以平移坐标解决，见 code2.cpp)
            if(i > 0) dp[i][j] += dp[i - 1][j];
            if(j > 0) dp[i][j] += dp[i][j - 1];
        }
    }
    cout << dp[n][m];
    return 0;
}