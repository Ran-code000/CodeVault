#include <iostream>

using namespace std;
int n, a[1001][1001], dp[1001][1001], maxx = 0;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            cin >> a[i][j];

    dp[1][1] = a[1][1];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + a[i][j];
            maxx = max(maxx, dp[i][j]);
        }
    }
    cout << maxx;
    return 0;
}