//每个单词可以使用两遍————可以拉直空间————s[n] 扩展为 s[2 * n] ———— 用正常的搜索方法的 vis[2 * n] 数组即可
//（个人习惯写 dfs 加上参数 dep，把第一层搜索一并放到主搜索函数里）
#include <iostream>
#include <string>

using namespace std;
int n, longest, vis[42];
string s[42], str, res;
char head;
int check(string s1, string s2){
    //检查相邻和包含关系 ———— at 和 atide 间不能相连
    //s1 为一直在变长的那个，从 s1 的末尾开始遍历
    for(int i = s1.size() - 1; i >= 0; i--)
    //例如 beast 和 astonish，如果接成一条龙则变为 beastonish
        if(s1.substr(i) == s2.substr(0, s1.size() - i)) return s1.size() - i;//返回重叠节的长度即第二个字串的索引
    return -1;
}
void dfs(string ans, int dep){
    //不能用 &ans，因为引用用的是 ans 整片区域，ans 和 s[i] 在两片不同的区域，此时 ans + s[i] 是语法错误
    if(ans.size() > longest){
        longest = ans.size();
        res = ans;
        //return; 只是负责找最值，不能结束
    }
    if(dep == 2 * n + 1) return;//通用终止条件，本题没有也行，有的话更保险
    //遍历数据
    for(int i = 1; i <= 2 * n; i++){
        //可以通过 dep 参数来控制搜索的层数（第一层和后面的层数）
        //也可以将第一层放到外面，就不需要 dep 参数，见 code2.cpp
        if(dep == 1 && s[i][0] == head && !vis[i]){
            //第一层：找龙头，开始拼接
            vis[i] = 1;
            dfs(ans + s[i], dep + 1);
            vis[i] = 0;//回溯
        }
        else if(dep >= 2 && !vis[i]){
            //第二层：拼接，找包含关系
            int pos = check(ans, s[i]);//开始截取的位置(下标)
            if(pos != -1){
                vis[i] = 1;
                dfs(ans + s[i].substr(pos), dep + 1);
                vis[i] = 0;//回溯
            }
        }
    }
}
int main(){
    cin >> n;
    //巧妙：每个单词可以用两次，数组扩成两倍
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = n + 1; i <= 2 * n; i++) s[i] = s[i - n];
    cin >> head;
    dfs(str, 1);
    //cout << str << endl;
    cout << res.length() << endl;
    return 0;
}