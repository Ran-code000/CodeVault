#include <iostream>
#include <string>

using namespace std;
int n, vis[42], maxx = 0;
string s[42], res;
char head;
int check(string s1, string s2){
    for(int i = s1.size() - 1; i >= 0; i--)
        if(s1.substr(i) == s2.substr(0, s1.size() - i)) return s1.size() - i;
    return 0;
}
void dfs(string ans, int dep){
    if(ans.size() > maxx){
        maxx = ans.size();
        res = ans;
    }
    for(int i = 1; i <= 2 * n; i++){
        if(dep == 1 && s[i][0] == head && !vis[i]){
            vis[i] = 1;
            dfs(ans + s[i], dep + 1);
            vis[i] = 0;
        }else if(dep >= 2 && !vis[i]){
            int pos = check(ans, s[i]);
            if(pos){
                vis[i] = 1;
                dfs(ans + s[i].substr(pos), dep + 1);
                vis[i] = 0;
            }
        }
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = n + 1; i <= 2 * n; i++) s[i] = s[i - n];
    cin >> head;
    dfs("", 1);
    cout << res.length();
    return 0;
}