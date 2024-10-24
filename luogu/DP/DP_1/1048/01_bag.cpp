#include <iostream>
//状压 dp
using namespace std;
int dp[31], w[31], c[31];
int W, n;
int main(){
    cin >> W >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = W; j >= w[i]; j--)// 01 背包逆序遍历
            dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    cout << dp[W];
    return 0;
}