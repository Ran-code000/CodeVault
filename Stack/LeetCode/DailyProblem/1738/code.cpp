//方法一：
//二维前缀和 + 排序
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> pre(n + 1, vector<int>(m + 1));
        vector<int> res;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m ; j++){
                pre[i][j] = pre[i - 1][j - 1] ^ pre[i - 1][j] ^ pre[i][j - 1] ^ matrix[i - 1][j - 1];
                res.push_back(pre[i][j]);
            }
        }
        sort(res.begin(), res.end(), greater<int>());
        return res[k - 1];
    }
};
// 时间复杂度：O(mnlog⁡(mn))。计算二维前缀和的时间复杂度为 O(mn)，排序的时间复杂度为 O(mnlog⁡(mn))，因此总时间复杂度为 O(mnlog⁡(mn))。
// 空间复杂度：O(mn)，即为存储二维前缀和需要的空间。


//方法二：
//二维前缀和 + 快速选择算法
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> pre(n + 1, vector<int>(m + 1));
        vector<int> res;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m ; j++){
                pre[i][j] = pre[i - 1][j - 1] ^ pre[i - 1][j] ^ pre[i][j - 1] ^ matrix[i - 1][j - 1];
                res.push_back(pre[i][j]);
            }
        }
        nth_element(res.begin(), res.begin() + k - 1, res.end());
        return res[k - 1];
    }
};
// 时间复杂度：O(mn)。计算二维前缀和的时间复杂度为 O(mn)，快速选择找出第 k 大的元素的期望时间复杂度为 O(mn)，
// 最坏情况下时间复杂度为 O((mn)^2), 因此总时间复杂度为 O(mn)。
// 空间复杂度：O(mn)，即为存储二维前缀和需要的空间。
