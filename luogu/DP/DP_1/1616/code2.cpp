#include <iostream>
// 125 MB 内存限制 ———— 整数型数组最大开到 3000 0000，bool 型最多在 1000 0000 左右
//本题需要状压 dp
using namespace std;
int M, n, w[10010], c[10010];
long long dp[10000010];//注意 10 的 7 次方 * 10 的 4 次方会爆 int，要开 long long 数组
int main(){
    cin >> M >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= n; i++)
        for(int j = w[i]; j <= M; j++)
            dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    cout << dp[M];
    return 0;
}