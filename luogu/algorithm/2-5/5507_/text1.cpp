#include <iostream>
#include <map>
#include <queue>

using namespace std;
struct node{
    int x[13], step = 0, path[18] = {};
}now, temp;
int a[13][5];
map<long long, int> vis;
queue<node> q;
long long to_num(int *x){
    long long sum = 0;
    for(int i = 1; i <= 12; i++) sum = sum * 10 + x[i];
    return sum; 
}
void bfs(){
    long long temp_num;
    while(!q.empty()){
        temp = now = q.front();
        q.pop();

        for(int i = 1; i <= 12; i++){
            now.x[a[i][now.x[i]]]++;
            if(now.x[a[i][now.x[i]]] == 5) now.x[a[i][now.x[i]]] = 1;
            now.x[i]++;
            if(now.x[i] == 5) now.x[i] = 1;
            temp_num = to_num(now.x);
            now.path[now.step++] = i;
            if(!vis[temp_num]){
                vis[temp_num] = 1;
                if(temp_num == 111111111111){
                    cout << now.step << "\n";
                    for(int j = 0; j < now.step; j++) cout << now.path[j] << " ";
                    return;
                }
                q.push(now);
            }
            now = temp;
        }
    }
}
int main(){
    for(int i = 1; i <= 12; i++)
        for(int j = 0; j < 5; j++)
            cin >> a[i][j];
    for(int i = 1; i <= 12; i++) now.x[i] = a[i][0];
    vis[to_num(now.x)] = 1;
    q.push(now);
    bfs();
    return 0;
}