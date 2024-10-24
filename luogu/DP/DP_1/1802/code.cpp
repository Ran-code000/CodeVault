#include <iostream>

using namespace std;
int n, x, c_win[1010], c_lose[1010], w[1010], dp[1010];
int main(){
    cin >> n >> x;
    for(int i = 1; i <= n; i++) cin >> c_lose[i] >> c_win[i] >> w[i];
    for(int i = 1; i <= n; i++){
        for(int j = x; j >= 0; j--){
            if(j >= w[i]) dp[j] = max(dp[j] + c_lose[i], dp[j - w[i]] + c_win[i]);
            else dp[j] = max(dp[j], dp[j] + c_lose[i]);  
        }
    }
    cout << 5 * (long long)dp[x];
    return 0;
}