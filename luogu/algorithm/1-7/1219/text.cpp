#include <iostream>

using namespace std;
int n, vis1[14], vis2[27], vis3[27], cnt = 0, a[14][14];

void vis(int i, int j, int flag){
    a[i][j] = flag; 
    //标记数组二维压缩到一维
    vis1[j] = flag;
    vis2[i - j + n] = flag;
    vis3[i + j] = flag;
}

void dfs(int i){
    if(i == n + 1){
        cnt++;
        if(cnt <= 3){
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    if(a[i][j] == 1) cout << j << " ";
            cout << "\n";
        }
        return;
    }
    for(int j = 1; j <= n; j++){
        if(!vis1[j] && !vis2[i - j + n] && !vis3[i + j]){
            vis(i, j, 1);
            dfs(i + 1);
            vis(i, j, 0);
        }
    }
}

int main(){
    cin >> n;
    dfs(1);
    cout << cnt;
    return 0;
}