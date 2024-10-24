#include <iostream>
#include <cstring>

using namespace std;
const string s = "yizhong"; 
int n, dx[8] = {1, 1, 1, -1, -1, -1, 0, 0}, dy[8] = {0, 1, -1, 0, 1, -1, 1, -1};
char a[101][101], ans[101][101];

void search(int x, int y){
    for(int k = 0; k < 8; k++){
        int flag = 1;
        //flag 被用来标记，如果是全局变量，在使用中可能会导致状态混乱
        //状态混乱的原因：
        //全局状态的覆盖：在遍历不同搜索方向时，每个方向的搜索都会修改全局 flag。如果在某一方向搜索失败（将 flag 置为0），
        //              即使后续的方向可能成功找到了单词，由于 flag 已被之前的搜索方向修改，这种“成功”的状态会被忽略。
        //错误的状态重置：若没有在每次搜索新方向前重置 flag。意味着一旦 flag 被设置为0，所有后续的搜索方向都会被错误地跳过，
        //              因为它们都会检测到 flag 为0的状态。
        for(int i = 0; i < 7; i++){
            //i 同时控制偏移量系数和 s[i]; 
            int bx = x + i * dx[k], by = y + i * dy[k];
            if(bx < 1 || bx > n || by < 1 || by > n || a[bx][by] != s[i]){
                flag = 0;
                break;
            }
        }
        if(flag){
            for(int i = 0; i < 7; i++){
                int bx = x + i * dx[k], by = y + i * dy[k];
                ans[bx][by] = a[bx][by];
            }
        }
    }
    return;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
            ans[i][j] = '*';
        }
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(a[i][j] == 'y') search(i, j);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << ans[i][j];
        }
        cout << "\n";
    }
        
    return 0;
}