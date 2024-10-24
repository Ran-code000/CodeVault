#include <iostream>
#include <climits>
using namespace std;
int s[4], a[21][21], minn = INT_MAX, ans = 0;

void dfs(int left, int right, int i, int dep){
    //搜s[i] - 1 个， 第s[i]个判断
    //跳过初始进入条件， 类比 2036
    if(dep == s[i] && (left || right)){
        minn = min(minn, max(left, right));
        return;
    }
    //left, right放到条件里就不需要在回溯
    dfs(left + a[i][dep], right, i, dep + 1);
    dfs(left, right + a[i][dep], i, dep + 1);
}
int main(){
    cin >> s[0] >> s[1] >> s[2] >> s[3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < s[i]; j++)
            cin >> a[i][j];
        dfs(0, 0, i, 0); //逐行判断
        ans += minn;
        minn = INT_MAX;//所有状态还原
    }
    cout << ans;
    return 0;
}