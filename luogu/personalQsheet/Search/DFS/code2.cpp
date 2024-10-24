#include <iostream>
using namespace std;
string s;
bool vis[7];
char ans[7];
void dfs(int dep){
    if(dep == s.size() + 1){
        //搜多少打印多少，前 dep - 1 层搜索， 第 dep 层判断
        for(int i = 1; i <= dep - 1; i++) printf("%c", ans[i]);
        //打印优化：优先使用c语言的输出
        printf("\n");
        return ;
    }
    //枚举方案数
    for(int i = 0; i < s.size(); i++){
        if(!vis[i]){
            vis[i] = 1;//标记
            ans[dep] = s[i];//搜素当前层
            dfs(dep + 1);//搜索下一层
            vis[i] = 0;//回溯w
        }
    }
}

int main(){
    cin >> s;
    dfs(1);
    return 0;
}