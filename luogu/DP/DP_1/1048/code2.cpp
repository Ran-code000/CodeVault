#include <iostream>
//一维状压 dp
using namespace std;
int W, n, w[101], c[101], dp[1001];
int main(){
    cin >> W >> n;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int i = 1; i <= W; i++)
        for(int j = W; j >= w[i]; j--)
            dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    cout << dp[W]; 
    return 0;
}