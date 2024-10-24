/*
4
2 3 0
1 8 7
5 4 6

1 2 3
5 8 0
4 6 7

1 2 3
0 5 8
4 6 7

0 1 2
4 5 3
6 7 8

0 1 2
3 4 5
6 7 8
UNSOLVABLE*/
// 40 分通过代码
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;
struct node{
    int x[10], step, path[15] = {};
}now, temp;
unordered_map<int, int> vis; //小 tips：unordered_map 可能会提供更好的性能，因为它提供平均常数时间复杂度的访问
int b[10] = {}, a[10] = {};
queue<node> q;
int to_num(int *x){
    int sum = 0; 
    for(int i = 0; i < 9; i++)
        sum = sum * 10 + x[i];
    return sum;
}
int *change_matrix(int type, int *x){
    int dx0[] = {1, 1, 3, -3, 0, 3, -3, -1, -1};
    int dx1[] = {0, 0, 0, 1, 1, -2, 0, 0, 0};
    switch (type){
        case 0:
            for(int i = 0; i < 9; i++) b[i + dx0[i]] = x[i];
            break;
        case 1:
            for(int i = 0; i < 9; i++) b[i + dx1[i]] = x[i];
            break;
    }
    return b;
}
void print(int *path, int pos, int endd){
    int n = path[pos], cnt = 0, k[10] = {};
    if(pos == 0){
        for(int i = 0; i < 9; i++){
            cout << a[i] << " ";
            if((i + 1) % 3 == 0) cout << "\n";
        }
        return;
    }
    if(pos == endd){
        for(int i = 0; i < 9; i++){
            cout << i << " ";
            if((i + 1) % 3 == 0) cout << "\n";
        }
        return;
    }
    while(n){
        k[cnt++] = n % 10;
        n /= 10;
    }
    for(int i = 8; i >= 0; i--){
        cout << k[i] << " ";
        if(i % 3 == 0) cout << "\n";
    }
    return;
}
void bfs(){
    int temp_num;
    while(!q.empty()){
        temp = now = q.front();
        q.pop();

        for(int i = 0; i < 2; i++){
            int *pt = change_matrix(i, now.x);
            //for(int i = 0; i < 9; i++) cout << pt[i] << " ";
            temp_num = to_num(pt);
            //cout << temp_num << "\n";
            if(!vis[temp_num]){
                if(temp_num == 12345678){
                    cout << now.step + 1<< "\n";
                    for(int i = 0; i <= now.step + 1; i++){
                        print(now.path, i, now.step + 1);
                        cout << "\n";
                    }
                    return;
                }
                vis[temp_num] = 1;
                now.path[++now.step] = temp_num;
                for(int i = 0; i < 9; i++) now.x[i] = pt[i];
                q.push(now);
            }
            now = temp;
        }
    }
    cout << "UNSOLVABLE" << endl;
    return;
}
int main(){
    int pos = 0;
    for(int i = 0; i < 9; i++){
        cin >> a[i];
        now.x[i] = a[i];
    }
    now.step = 0;
    vis[to_num(now.x)] = 1;
    q.push(now);
    bfs();
    return 0;
}