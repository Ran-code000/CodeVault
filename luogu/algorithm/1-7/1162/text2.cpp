#include <iostream>

using namespace std;
int n, a[31][31];
void dfs(int x, int y){
    if(x < 0 || x > n || y < 0 || y > n) return; //先判断边界
    if(a[x][y] != 0) return;
    a[x][y] = 3;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
    for(int i = 0; i < n; i++) dfs(i, 0);
    for(int i = 0; i < n; i++) dfs(i, n - 1);
    for(int i = 0; i < n; i++) dfs(0, i);
    for(int i = 0; i < n; i++) dfs(0, n - 1);
    for(int i = 0; i <  n; i++){
        for(int j = 0; j < n; j++){
            if(a[i][j] == 3) cout << 0 << " ";
            if(a[i][j] == 1) cout << 1 << " ";
            if(a[i][j] == 0) cout << 2 << " ";
        }
        cout << "\n";
    }
    return 0;
}