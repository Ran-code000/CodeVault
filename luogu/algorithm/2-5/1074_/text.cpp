#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node{
    int x, y, srow, scol;
};
vector<node> v;
int a[10][10], n = 0, ans = -1, row[10][10], col[10][10], nine[10][10], srow, scol, vis[10][10];
bool cmp(node a, node b){
    if(a.x == b.x && a.srow == b.srow) return a.scol > b.scol;
    else if(a.srow == b.srow) return a.x > b.x;
    else return a.srow > b.srow;
}
int score(){
    int s = 0, x;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(i == 0 || i == 8 || j == 0 || j == 8) x = 6;
            else if(i == 1 || i == 7 || j == 1 || j == 7) x = 7;
            else if(i == 2 || i == 6 || j == 2 || j == 6) x = 8;
            else if(i == 3 || i == 5 || j == 3 || j == 5) x = 9;
            else x = 10;
            s += x * a[i][j];
        }
    }
    return s;
}
void dfs(int dep, int pos){
    if(dep == n){
        ans = max(ans, score());
        return;
    }
    for(int i = 1; i <= 9; i++){
        int bx = v[pos].x, by = v[pos].y, bnine = v[pos].x / 3 * 3 + v[pos].y / 3;
        if(row[bx][i] || col[by][i] || nine[bnine][i]) continue;
        a[bx][by] = i;
        row[bx][i] = col[by][i] = nine[bnine][i] = 1;
        dfs(dep + 1, pos + 1);
        row[bx][i] = col[by][i] = nine[bnine][i] = 0;
        a[bx][by] = 0;
    }
}
int main(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> a[i][j];
            if(a[i][j]){
                row[i][a[i][j]] = 1;
                col[j][a[i][j]] = 1;
                nine[i / 3 * 3 + j / 3][a[i][j]] = 1;
            }else n++;
        }
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(!a[i][j]){
                for(int k = 1; k <= 9; k++){
                    if(row[i][k]) srow++;
                    if(col[j][k]) scol++;
                }
                v.push_back({i, j, srow, scol});
            }
        }
    }
    sort(v.begin(), v.end(), cmp);
    dfs(0, 0); 
    cout << ans;
    return 0;
}