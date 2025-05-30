//滚动数组优化
class Solution {
public:
	int uniquePaths(int m, int n) {
        //int dp[m][n];
        int dp[2][n];
        // for(int i = 0; i < m; i++) dp[i][0] = 1;
        // for(int j = 0; j < n; j++) dp[0][j] = 1;
		for (int i = 0; i < 2; i++) dp[i][0] = 1;
		for (int j = 0; j < n; j++) dp[0][j] = 1;
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
                //dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				dp[i % 2][j] = dp[i % 2][j - 1] + dp[(i - 1) % 2][j];
        //return dp[m - 1][n - 1];
		return dp[(m - 1) % 2][n - 1];
	}
};