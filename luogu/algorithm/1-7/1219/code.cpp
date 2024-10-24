#include <iostream>

using namespace std;
int n, flag, cnt = 0;
int vis1[13]/*列*/, vis2[26]/*左上到右下*/, vis3[26]/*右上到左下*/;
int a[13][13];

void vis(int i, int j, int flag){
    a[i][j] = flag;
    vis1[j] = flag;
    //找到对角线上端元素满足的规律
    vis2[i - j + n] = flag;
    vis3[i + j] = flag;
}

void dfs(int i){
    if(i == n){
        //前 n - 1 层搜索，第 n 层判断
        cnt++;
        if(cnt <= 3){
            for(int i= 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    if(a[i][j] == 1) cout << j + 1 << " ";
            cout << "\n";
        }
    }
    //对每一行搜每一列
    for(int j = 0; j < n; j++){
        if(!vis1[j] && !vis2[i - j + n] && !vis3[i + j]){
            vis(i, j, 1);
            dfs(i + 1);
            vis(i, j, 0);
        }
        
    }
}
int main(){
    cin >> n;
    dfs(0);
    cout << cnt;
    return 0;
}