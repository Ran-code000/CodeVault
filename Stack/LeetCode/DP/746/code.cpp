// 其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
// 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
// 请你计算并返回达到楼梯顶部的最低花费
#define min(a, b) (a > b ? b : a)
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int dp[cost.size() + 1];
        //初始化dp边界
        dp[0] = 0;
        dp[1] = cost[0];
        for(int i = 2; i <= cost.size(); i++) dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i - 1];
        return min(dp[cost.size()], dp[cost.size() - 1]);
    }
};