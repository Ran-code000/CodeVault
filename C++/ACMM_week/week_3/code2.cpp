#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;
queue<string> q;
unordered_map<string, bool> vis;
void change3(int aa, int bb, int cc, int dd, const string& temp);
void change2(int aa, int bb, int cc, const string& temp);
void change4(int aa, int bb, int cc, int dd, int ee, const string& temp);
string ans = "123456780";
int n;
bool bfs(int id){
    while(!q.empty()){
        string temp = q.front();
        q.pop();
        for(int i = 0; i < 9; i++) if(temp[i] == '0') id = i;

        cout << "temp:" << temp << " id : " << id << "    " << vis[temp] << endl;
        if(temp == ans) return 1;
        if(vis[temp]) continue;
        else{
            if(id == 8){
                change2(8, 5, 7, temp);
            }else if(id == 0){
                change2(0, 1, 3, temp);
            }else if(id == 1){
                change3(1, 0, 2, 4, temp);
            }else if(id == 3){
                change3(3, 0, 4, 6, temp);
            }else if(id == 5){
                change3(5, 2, 4, 8, temp);
            }else if(id == 7){
                change3(7, 4, 6, 8, temp);
            }else if(id == 2){
                change2(2, 1, 5, temp);
            }else if(id == 6){
                change2(6, 3, 7, temp);
            }else if(id == 4){
                change4(4, 1, 3, 5, 7, temp);
            }
        }
        
    }
    return 0;    
}
void change2(int aa, int bb, int cc, const string& temp){
    string s = "";
    int a[9];
    for(int i = 0; i < 9; i++) a[i] = (int)temp[i] - 48;
    swap(a[aa], a[bb]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[bb]);
    s = "";
    swap(a[aa], a[cc]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[cc]);
}
void change3(int aa, int bb, int cc, int dd, const string& temp){
    string s = "";
    int a[9];
    for(int i = 0; i < 9; i++) a[i] = (int)temp[i] - 48;
    swap(a[aa], a[bb]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[bb]);
    s = "";
    swap(a[aa], a[cc]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[cc]);
    s = "";
    swap(a[aa], a[dd]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[dd]);
}
void change4(int aa, int bb, int cc, int dd, int ee, const string& temp){
    string s = "";
    int a[9];
    for(int i = 0; i < 9; i++) a[i] = (int)temp[i] - 48;
    swap(a[aa], a[bb]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[bb]);
    s = "";
    swap(a[aa], a[cc]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[cc]);
    s = "";
    swap(a[aa], a[dd]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[dd]);
    s = "";
    swap(a[aa], a[ee]);
    for(int i = 0; i < 9; i++) s += to_string(a[i]);
    if(!vis[s]) q.push(s), vis[s] = 1;
    swap(a[aa], a[ee]);
}
int main(){
    cin >> n;
    while(n--){
        int a, ttt;
        string tt = "";
        for(int i = 0; i < 9; i++){
            cin >> a;
            if(a == 0) ttt = i;
            string t = to_string(a);
            tt += t;
        }
        q.push(tt);
        vis[tt] = 1;
        cout << "tt :  " << tt  << " ttt:" << ttt << endl;
        if(bfs(ttt)) cout << "Yes\n";
        else cout << "No\n";
        while (!q.empty()) q.pop();
        vis.clear();
    }
    return 0;
}