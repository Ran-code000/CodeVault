#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
vector<int> s, ans, vis;
int n, k, sum = 0, cnt = 0;

bool isPrime(int n){
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i += 2)
        if(n % i == 0) return false;
    return true;
}

void dfs(int dep, int start){
    if(dep == k){
        if(isPrime(sum)) cnt++;
        for(int i = 0; i < dep; i++) cout << ans[i] << " ";
        cout << "\n";
        return;
    }
    for(int i = start; i < n; i++){
        if(!vis[i]){
            vis[i] = 1;
            sum += s[i];
            ans.push_back(s[i]);
            dfs(dep + 1, i + 1);
            vis[i] = 0;
            sum -= s[i];
            ans.pop_back();
        }
    }
}
int main(){
    cin >> n >> k;
    s.resize(n);
    vis.resize(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end());
    dfs(0, 0);
    cout << cnt;
    return 0;
}