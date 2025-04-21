//模拟问题
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        vector<int> res(n);
        int len = rolls.size() + n, sum = len * mean;
        for(int i : rolls) sum -= i;
        if(sum > 6 * n || sum < n) return {};
        else{int temp = sum / n, t = sum % n; for(int i = 0; i < n; i++) res[i] = temp + (i < t ? 1 : 0);}
        return res;
    }
};