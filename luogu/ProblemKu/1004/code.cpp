#include <iostream>
using namespace std;
int n, a[11][11], dp[11][11][11][11];
//四维dp,dp[i][j][k][l]表示第一遍走到点[i,j],第二遍走到点[k,l]的最优解
int main(){
    cin >> n;
    int xx, yy, pp;
    while(cin >> xx >> yy >> pp && (xx || yy || pp)) a[xx][yy] = pp;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++)
                for(int l = 1; l <= n; l++){
                    dp[i][j][k][l] = max(max(dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1]), max(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1])) + a[i][j] + a[k][l];
                    if(i == k && j == l) dp[i][j][k][l] -= a[i][j];
                }
    cout << dp[n][n][n][n];
    return 0;
}
