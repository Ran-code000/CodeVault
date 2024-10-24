#include<iostream>
using namespace std;
int n, dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0}, dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
char str[200], a[101][101];
bool vis[101][101];
bool dfs(int x, int y, char ch, int k){
	if(ch =='g'){//最后一个字母判断成功，标记，返回
		vis[x][y] = 1;
		return 1;
	}
	int bx = x + dx[k], by = y + dy[k];
	if(bx >= 1 && bx <= n && by >= 1 && by <= n && a[bx][by] == str[ch]){
        if(dfs(bx, by, str[ch], k)){
            //一般为回溯取消标记，但这里不需要回溯取消标记，而是需要在成功完成一次搜索后去标记搜索的路径
            vis[x][y]=1;
            return 1;
        }
    }
	return 0;
}
int main(){
	str['y'] = 'i';
	str['i'] = 'z';
	str['z'] = 'h';
	str['h'] = 'o';
	str['o'] = 'n';
	str['n'] = 'g';//把单词串在一起
	cin >> n;
	for(int i = 1; i <= n; i++)
	    for(int j = 1; j <= n; j++)
	        cin >> a[i][j];
	for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(a[i][j] == 'y'){
                for(int k = 0; k < 8; k++){
                    if(dfs(i, j, 'y', k)) vis[i][j] = 1; 
                }
            }
        }
    }  
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
		    if(vis[i][j]) cout << a[i][j];
		    else cout << '*';
		cout << "\n";
	}
	return 0;
}
