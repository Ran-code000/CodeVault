#include <iostream>
//二维数组完全背包（不过）———— 数据量过大，内存会爆
using namespace std;
int W, n, w[10010], c[10010];
long long dp[10010][100010];
int main(){
    cin >> W >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= W; j++)
            if(j < w[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i][j], dp[i][j - w[i]] + c[i]);
    cout << dp[n][W];
    return 0;
}