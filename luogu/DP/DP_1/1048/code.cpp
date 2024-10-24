#include <iostream>
//二维数组 dp
using namespace std;
int W, n, w[101], c[101], dp[101][1001];  
int main(){
    cin >> W >> n;
    //注意下标均从 1 开始
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= W; j++)
            if(j < w[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], c[i] + dp[i - 1][j - w[i]]);
            // max (不选（沿用上一层的状态）,选（选中的价值 + 除去选中耗费的代价还能选的价值）)
            //从二维数组上区别 01 背包和完全背包也就是状态转移方程就差别在采第 i 种草药时，
            //完全背包在选择采这个草药时，最优解是同行的那一个，见 1616 code1.cpp
            //01 背包比较的是上一行的那一个
    cout << dp[n][W];
    return 0;
}