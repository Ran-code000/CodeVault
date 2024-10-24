#include <iostream>
#include <queue>
//普通 bfs 找最短路径 ———— 本题难点：变换坐标系到我们使用二维数组（矩阵）的正常逻辑
//用数组模拟队列的实现 ———— 见 code1.cpp
using namespace std;
struct node{ 
  int x, y, step;
};
int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1}, dy[] = {0, 0, -1, 1, -1, 1, -1, 1}, vis[1005][1005], ans, n, m, x, y;;
char a[1005][1005]; 
long long cnt = 1;
queue<node> q;
void bfs(){
  while(!q.empty()){
      node t = q.front();
      q.pop(); 
      ans = t.step;
      
      for(int i = 0; i < 8; i++){
          int bx = t.x + dx[i], by = t.y + dy[i];
          if(bx < 1 || bx > n || by < 1 || by > m) continue;
          if(a[bx][by] == '.' && !vis[bx][by]){
            cnt++;
            if(cnt == n * m){
                cout << t.step + 1;
                return;
            }
          	vis[bx][by] = 1;
  		    q.push({bx, by, t.step + 1}); 
  		}
      }
  }
  //cout << ans; 
} 
int main(){
    cin >> n >> m >> x >> y;//按正常顺序输入
    vis[x][y] = 1;
    q.push({x, y, 0});

    //起点一般在左上角，但本题起点在左下角，为保证 x, y相对位置不变（(x, y) 还是 (x, y)），将坐标系顺时针旋转 90 度
    for(int j = m; j >= 1; j--){
        for(int i = 1; i <= n; i++){
            cin >> a[i][j];
            if(a[i][j] == '*') cnt++;
        }
    }//注意此时 j 对应 m，i 对应 n
    //这样才能保证变换坐标系后所有输出搜索逻辑按正常进行
    /*for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) cout << a[i][j];
        cout << "\n";
    }*/
    //否则若在输入时就变换了 n, m, x, y 的位置，则正常输出的逻辑需要变换为 i 对应 m，j 对应 n，
    //显然不满足我们想要的 ———— 变换完坐标系后其他的均相同
    bfs(); 
    return 0; 
}
