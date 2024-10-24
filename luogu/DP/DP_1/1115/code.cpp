#include <iostream>

using namespace std;
int n, maxx, dp[200001], a[200001];
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        dp[i] = a[i];
        if(i == 0){
            maxx = dp[0];
            continue;
        }
        dp[i] = max(dp[i - 1] + a[i], dp[i]);
        maxx = max(maxx, dp[i]);
    }
    cout << maxx;
    return 0;
}