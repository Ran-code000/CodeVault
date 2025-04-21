//类比 198
// 给你一个整数数组 nums ，你可以对它进行一些操作。
// 每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。
//之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
// 开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int len = nums[nums.size() - 1] + 1, a[len], dp[len];
        memset(a, 0, sizeof(int) * len);
        for(int i : nums) a[i]++;
        dp[0] = 0, dp[1] = max(a[0], a[1]);
        for(int i = 2; i < len; i++) dp[i] = max(i * a[i] + dp[i - 2], dp[i - 1]);
        return dp[len - 1];
    }
};