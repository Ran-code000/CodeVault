#include <iostream>

//求联通块方法

using namespace std;
int n, a[31][31];

void dfs(int x, int y){
    //先进行边界和状态检查：在dfs函数内，应首先检查当前位置是否越界或已经访问（即a[x][y]不为0），如果是，则立即返回
    if(x < 1 || x > n || y < 1 || y > n || a[x][y] != 0) return;
    a[x][y] = 1;//先进行边界和状态检查再修改 a[x][y] 的值
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
            if(a[i][j] == 1) a[i][j] = -1;
        }
    }
    for(int i = 1; i <= n; i++){
        dfs(i, 1);
        dfs(i, n);
    }
    for(int j = 1; j <= n; j++){
        dfs(1, j);
        dfs(n, j);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(a[i][j] == 1) cout << 0 << " ";
            else if(a[i][j] == -1) cout << 1 << " ";
            else if(a[i][j] == 0) cout << 2 << " ";
        }
        cout << "\n";
    }
    return 0;
}