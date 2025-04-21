//泰波那契序列：T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn
class Solution {
public:
    int tribonacci(int n) {
        if(n == 0) return 0;
        else if(n <= 2) return 1;
        int p = 0, q = 1, r = 1, s = 2;
        for(int i = 3; i < n; i++) p = q, q = r, r = s, s = p + q + r;
        return s;
    }
};