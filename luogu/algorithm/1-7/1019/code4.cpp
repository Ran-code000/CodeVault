#include <iostream>
#include <string>

using namespace std;
int n, vis[21], maxx = 0;
string s[21], res;
char head;
int check(string s1, string s2){
    for(int i = s1.size() - 1; i >= 0; i--)
        //s.substr() ———— 只有一个参数，意思为从参数位置到末端
        //           ———— 有两个参数，意思为从第一个参数的位置截取第二个参数的长度
        if(s1.substr(i) == s2.substr(0, s1.size() - i)) return s1.size() - i;
    return 0;
}
void dfs(string ans, int dep){
    //ans 只是用来拼接，结果保存在 res 中
    if(ans.size() > maxx){
        maxx = ans.size();
        res = ans;
    }
    for(int i = 1; i <= n; i++){
        if(dep == 1 && s[i][0] == head && vis[i] < 2){
            vis[i]++;
            dfs(ans + s[i], dep + 1);
            vis[i]--;
        }else if(dep >= 2 && check(ans, s[i]) && vis[i] < 2){
            vis[i]++;
            dfs(ans + s[i].substr(check(ans, s[i])), dep + 1);
            vis[i]--;
        }
    }
}
int main(){
    cin >>  n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    cin >> head;
    dfs("", 1);
    //cout << res << "\n" << res.size();
    cout  << res.size();
    return 0;
}