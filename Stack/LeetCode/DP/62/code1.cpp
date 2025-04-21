// 法2： 空间优化
//!!!
// memset 函数的原型是：void *memset(void *ptr, int value, size_t num);
// memset 将从 ptr 开始的内存块的前 num 字节设置为 value 的值。
//这里，value 被解释为 unsigned char，即一个字节。
//因此，如果使用 memset(dp, 1, sizeof(int) * n); 会将 dp 数组的前 sizeof(int) * n 个字节设置为 1
//（即每个字节都设为二进制的 00000001）。

// 问题的根源：
// 假设 int 类型是 4 字节（32 位），那么 memset(dp, 1, sizeof(int) * n); 
// 实际上会将每个 int 元素的每个字节都设置为 1。
// 但是，这样设置后，每个 int 元素的值将不是 1，而是 0x01010101（十六进制表示），即十进制数 16843009。

// 简单来说：
// memset(dp, 1, sizeof(int) * n); 设置的是字节级别的值，而不是整数级别的值。
// 每个 int 值将被设置为 0x01010101 而不是 1。

// vector<int> dp(n, 1); 的工作机制：
// vector<int> dp(n, 1); 这行代码使用的是 std::vector 的构造函数，它会创建一个包含 n 个元素的向量，每个元素都被初始化为 1。
// 这里，每个 int 元素的值确实是 1，与预期一致。

// 比较总结：
// memset(dp, 1, sizeof(int) * n); 实际上将每个 int 元素初始化为 0x01010101，而不是 1，因为它操作的是字节级别的内存。
// vector<int> dp(n, 1); 正确地将每个 int 元素初始化为 1，因为它使用的是 vector 的构造函数。
// 因此，memset 并不适用于将 int 数组（或其他多字节类型）初始化为特定的值（除非是 0，因为所有字节都设置为 0 是有效的）
//。对于 int 数组的这种初始化，应该使用循环或者 STL 容器提供的初始化方法，如 std::vector。

class Solution {
public:
	int uniquePaths(int m, int n) {
        //int dp[m][n];
        // int dp[n];
        // memset(dp, 1, sizeof(int) * n); ❌
        vector<int> dp(n, 1);
		for (int i = 1; i < m; i++) {
            // for(int i = 0; i < m; i++) dp[i][0] = 1;
            // for(int j = 0; j < n; j++) dp[0][j] = 1;
			dp[0] = 1;
			for (int j = 1; j < n; j++) dp[j] = dp[j - 1] + dp[j];//dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
		return dp[n - 1];
	}
};