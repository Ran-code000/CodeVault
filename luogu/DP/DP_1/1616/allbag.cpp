#include <iostream>
//完全背包优化版本
using namespace std;
int M, n, w[10010], c[10010];
long long dp[10000010];
int main(){
    cin >> M >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = w[i]; j <= M; j++)//正序遍历
            dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    cout << dp[M];
    return 0;
}