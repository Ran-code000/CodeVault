#include <iostream>
#include <algorithm>
//深搜 + 排序优化 ———— 40分
//有记忆化优化比较低效 ———— 本题数据重复可能很少
using namespace std;
long long n, m, a[45], ans = 1, x = 0;
void dfs(int start, long long money){
    if(a[start] > money) return;
    for(int i = start; i <= n; i++){
        if(a[i] <= money){
            ans++;
            dfs(i + 1, money - a[i]);
        }else return;
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] > m) x++;
    }
    sort(a + 1, a + 1 + n);
    dfs(1, m);
    cout << ans;
    return 0;
}