#include <iostream>
#include <climits>
using namespace std;
int s[4], a[21][21], minn = INT_MAX, ans = 0;

void dfs(int left, int right, int i, int dep){
    if(dep == s[i] && (left || right)){
        minn = min(minn, max(left, right));
        return;
    }
    dfs(left + a[i][dep], right, i, dep + 1);
    dfs(left, right + a[i][dep], i, dep + 1);
}
int main(){
    cin >> s[0] >> s[1] >> s[2] >> s[3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < s[i]; j++)
            cin >> a[i][j];
        dfs(0, 0, i, 0);
        ans += minn;
        minn = INT_MAX;
    }
    cout << ans;
    return 0;
}

