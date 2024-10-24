#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node{
    int x, y, srow, scol;//某个数所在行列有多少个数已经被填
};
vector<node> v;
int a[10][10], n, ans = -1;
bool row[10][10], col[10][10], nine[10][10];//行，列，九宫格
bool cmp(node a, node b){
    if(a.srow == b.srow && a.x == b.x) return a.scol > b.scol;//两行被填数的个数相同时，且行号相同时，按列排列
    if(a.srow == b.srow) return a.x > b.x;//两行被填数的个数相同时，按行排列
    return a.srow > b.srow;//两行被填数的个数不同时，被填个数排列（该数所在行列填的多的先填该数 ———— 枚举方案数小，分支小，优化）
}
int score(){
    int s = 0, x;
    //cout << "\n";
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            //cout << a[i][j] << " ";
            if(i == 0 || i == 8 || j == 0 || j == 8) x = 6;
            else if(i == 1 || i == 7 || j == 1 || j == 7) x = 7;
            else if(i == 2 || i == 6 || j == 2 || j == 6) x = 8;
            else if(i == 3 || i == 5 || j == 3 || j == 5) x = 9;
            else x = 10;
            s += x * a[i][j];
        }
        //cout << "\n";
    }
    return s;
}
//当前要填节点位置，填到第几个节点
void dfs(int pos, int dep){
    if(dep == n){
        ans = max(ans, score());
        return;
    }
    for(int i = 1; i <= 9; i++){
        int nine_pos = v[pos].x / 3 * 3 + v[pos].y / 3;
        if(row[v[pos].x][i] || col[v[pos].y][i] || nine[nine_pos][i]) continue;
        row[v[pos].x][i] = col[v[pos].y][i] = nine[nine_pos][i] = 1;//标记行，列，九宫格
        a[v[pos].x][v[pos].y] = i;//填值
        dfs(pos + 1, dep + 1);//已经排序（从大到小，逐行填满），不能填完 8 行填 6 行再填 8 行等等
        a[v[pos].x][v[pos].y] = 0;//回溯
        row[v[pos].x][i] = col[v[pos].y][i] = nine[nine_pos][i] = 0;//回溯，解标记行，列，九宫格
    }
}
int main(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> a[i][j];
            //初始化还没被填的点，之后搜索以这个初始化为基础
            if(a[i][j]){
                row[i][a[i][j]] = 1;// row[第几行][哪个数字]
                col[j][a[i][j]] = 1;// col[第几列][哪个数字]
                nine[i / 3 * 3 + j / 3][a[i][j]] = 1;// nine[第几个九宫格][哪个数字]
            }else n++;
        }
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int srow = 0, scol = 0;
            if(!a[i][j]){
                //某个数所在行列有多少个数已经被填
                for(int k = 1; k <= 9; k++){
                    if(row[i][k]) srow++;
                    if(col[j][k]) scol++;
                }
                v.push_back({i, j, srow, scol});
            }
        }
    }
    sort(v.begin(), v.end(), cmp);//按方案数的多少填（方案数少的先填 ———— 减少深搜次数，优化方案）
    dfs(0, 0);
    //验证每个数的数据准备（行，列，所在行被填数个数，所在列被填数个数）
    //for(int i = 0; i < v.size(); i++) cout << v[i].x << " " << v[i].y << " " << v[i].srow << " " << v[i].scol << "\n";
    /*验证行（列，九宫格）的标记情况
    cout << "row:\n";
    for(int i = 0; i < 9; i++){
        for(int j = 1; j <= 9; j++) cout << row[i][j] << " ";
        cout << "\n";
    }
    */
    cout << ans;
    return 0;

}