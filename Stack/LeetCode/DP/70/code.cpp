//斐波那契数列 ———— 滚动数组优化 ———— 简单的状态转移方程；
class Solution {
public:
    int climbStairs(int n) {
        int p = 0, q = 0, r = 1;
        for(int i = 0; i < n; i++) p = q, q = r, r = p + q;
        return r;
    }
};