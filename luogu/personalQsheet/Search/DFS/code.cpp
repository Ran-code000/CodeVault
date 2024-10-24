#include <iostream>
#include <vector>

using namespace std;
int n, m, ans, f[1001][1001];
char a[1001][1001];
void dfs(int x, int y){
    if(x < 1 || x > n || y < 1 || y > m || a[x][y] == '0') return ;
    a[x][y] == '0';
    dfs(x + 1, y);//下
    dfs(x - 1, y);//上
    dfs(x, y + 1);//右
    dfs(x, y - 1);//左
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i][j] != '0'){
                ans++;
                dfs(i, j);
            }
        }
    }
    cout << ans;
    return 0;
}