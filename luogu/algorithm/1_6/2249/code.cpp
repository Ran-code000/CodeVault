#include <iostream>
#include <vector>
#include <map>
using namespace std;
int n, m; //a[1000010], b[1000010], vis[1000000010];
vector<int> a, b;
map<int, int> vis;
int main(){
    cin >> n >> m;
    a.resize(n);
    b.resize(m);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    int pos = 0, start = 0;
    for(int i = 0; i < m; i++){
        if(vis[b[i]]) continue;
        for(int j = start; j < n; j++){
            if(a[j] == b[i]){
                vis[a[j]] = 1;
                cout << j + 1 << " ";
                start = j + 1;
                break;
            }else if(a[j] > b[i]){
                cout << -1 << " ";
                break;
            }else continue; 
        }
    }
    return 0;
}