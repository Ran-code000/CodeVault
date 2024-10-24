#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
//二分搜索，折半搜索优化
using namespace std;
long long n, m, a[45], ans = 1;
vector<long long> sa, sb;//记录不超过 m 的所有花钱方案
//起始点，当前已经花了多少钱，二分搜索的类型（前半段还是后半段）
void dfs(int start, long long spend_money, int type){
    if(m - spend_money < a[start]) return;
    int endd = n;
    if(type == 0) endd = n / 2;//搜前半部分
    for(int i = start; i <= endd; i++){
        if(m - spend_money >= a[i]){
            //ans++;
            if(type == 0) sa.push_back(spend_money + a[i]);
            else sb.push_back(spend_money + a[i]);
            dfs(i + 1, spend_money + a[i], type);
        }else return;
    }
}
int main(){
    //9 120
    //10 20 30 40 50 60 70 80 90
    cin >> n >> m;
    int x = 0;//一定记得初始化，否则 x 的值不明确
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] > m) x++;
    }
    sort(a + 1, a + 1 + n);
    n -= x;//剪枝
    //dfs(1, m);
    dfs(1, 0, 0);//搜前半段
    dfs(n / 2 + 1, 0, 1);//搜后半段
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    
    /*
    for(int i = 0; i < sa.size(); i++) cout << sa[i] << " ";//前半段搜出来的所有花钱组合（前半段钱少方案多）
    //10 20 30 30 40 40 50 50 60 60 70 70 80 90 100
    cout << "\n";
    for(int i = 0; i < sb.size(); i++) cout << sb[i] << " ";//后半段搜出来的所有花钱组合（后半段钱多方案少）
    //50 60 70 80 90 110 120
    cout << "\n";
    */

    //以后半段的数为基准做二分查找
    long long b_leave_money, max_pos;
    for(int i = 0; i < sb.size(); i++){
        b_leave_money = m - sb[i];
        max_pos = upper_bound(sa.begin(), sa.end(), b_leave_money) - sa.begin();// sa 中满足条件的最大下标索引
        //cout << b_leave_money << " " << max_pos << "\n";
        ans += max_pos;
    }
    ans += (sa.size() + sb.size());
    cout << ans;
    return 0;
}