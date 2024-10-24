//方法更通用，若对于单词可以出现的次数更多时
#include <iostream>
#include <string>

using namespace std;
int n, vis[21], maxx = 0;
string s[21], res;
char head;
int check(string s1, string s2){
    for(int i = s1.size() - 1; i >= 0; i--)
        if(s1.substr(i) == s2.substr(0, s1.size() - i)) return s1.size() - i;
    return 0;
}
void dfs(string ans, int dep){
    if(ans.size() > maxx){
        //这里只是为更新最大值，千万不能 return;
        maxx = ans.size();
        res = ans;
    }
    for(int i = 1; i <= n; i++){
        if(vis[i] < 2){
            //单词能使用且符合拼接条件
            int pos = check(ans, s[i]);
            if(pos){
                vis[i]++;
                dfs(ans + s[i].substr(pos), dep + 1);
                vis[i]--;
            }
        }
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    cin >> head;
    for(int i = 1; i <= n; i++){
        //第一层判断
        if(s[i][0] == head){
            vis[i]++;
            dfs(s[i], 1);
            vis[i]--;
        }
    }
    cout << res.size() << endl;
    return 0;
}