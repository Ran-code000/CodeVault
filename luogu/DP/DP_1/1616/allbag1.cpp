#include <iostream>
//完全背包枚举 k 版本 ———— 时间消耗较 allbag.cpp 长
using namespace std;
int W, n, w[10010], c[10010];
long long dp[10000001];
int main(){
    cin >> W >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = W; j >= w[i]; j--)
            for(int k = 1; k <= j / w[i]; k++)
                dp[j] = max(dp[j], dp[j - k * w[i]] + k * c[i]);
    cout << dp[W];
    return 0;
}