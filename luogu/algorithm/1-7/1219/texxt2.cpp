#include <iostream>

using namespace std;
int n, vis1[14], vis2[27], vis3[27], a[14][14], ans = 0;;

void vis(int i, int j, int flag){
    a[i][j] = flag;
    vis1[j] = flag;
    vis2[i - j + n] = flag;
    vis3[i + j] = flag;
}

void dfs(int dep){
    if(dep == n + 1){
        ans++;
        if(ans > 3) return;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(a[i][j] == 1) cout << j << " ";
            }
        }
        cout << "\n";
        return;
    }
    for(int j = 1; j <= n; j++){
        if(!vis1[j] && !vis2[dep - j + n] && !vis3[dep + j]){
            vis(dep, j, 1);
            dfs(dep + 1);
            vis(dep, j, 0);
        }
    }
}
int main(){
    cin >> n;
    dfs(1);
    cout << ans;
    return 0;
}

