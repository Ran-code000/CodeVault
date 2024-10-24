//滚动数组优化
#include <iostream>

using namespace std;
int n, m, xx, yy;
int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2}, dy[8] = {1, -1, 2, -2, 2, -2, 1, -1}, vis[23][23];
long long dp[2][23]; //答案可能很大，要开 long long
int main(){
    cin >> n >> m >> xx >> yy;
    //先平移再初始化
    n += 2, m += 2, xx += 2, yy += 2; //进一步平移，不用特判 i > 0，j > 0 的情况，也不用特判标马时数组越界的情况 
    vis[xx][yy] = 1; //初始化
    for(int i = 0; i < 8; i++){
        int bx = xx + dx[i], by = yy + dy[i];
        vis[bx][by] = 1;
    }
    dp[2][2] = 1; //初始化
    for(int i = 2; i <= n; i++){
        for(int j = 2; j <= m; j++){
            if(vis[i][j] || i == 2 && j == 2) continue; //跳过标记点和起点
            dp[i & 1][j] = dp[(i - 1) & 1][j] + dp[i & 1][j - 1];      
        }
    }
    cout << dp[n & 1][m];
    return 0;
}