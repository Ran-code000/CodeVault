#include <iostream>
#include <string>
#include <queue>
//用 bfs ，用到字符串的 find 和 replace 函数
using namespace std;
struct node{
    string s;
    int step;
};
int n;
string a[11], b[11], sa, sb;
queue<node> q;
int bfs(){
    while(!q.empty()){
        node t = q.front();
        q.pop();

        if(t.step == 10) break;
        if(t.s == sb) return t.step;

        for(int i = 0; i < n; i++){
            int find_index = t.s.find(a[i]);
            while(find_index != -1){
                string temp = t.s;
                temp.replace(find_index, a[i].size(), b[i]);//替换a中pos开始往后len的这些字符为b
                q.push({temp, t.step + 1});
                find_index = t.s.find(a[i], find_index + 1);
            }
        }
    }
    return -1;
}
int main(){
    cin >> sa >> sb;
    while(cin >> a[n] >> b[n]) n++;
    q.push({sa, 0});
    int min_steps = bfs();
    if(min_steps == -1) cout << "NO ANSWER!" << "\n";
    else cout << min_steps;
    return 0;
}