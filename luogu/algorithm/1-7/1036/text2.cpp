#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
int n, k, vis[21], ans = 0;
vector<int> a;
bool isPrime(int n){
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i += 2){
        if(n % i == 0) return false;
    }
    return true;
}

void dfs(int sum, int dep, int start){
    if(dep == k && isPrime(sum)){
        ans++; //只需统计方法数，无需保存路径，类比 2404
        return;
    }
    for(int i = start; i < n; i++){
        if(!vis[i]){
            vis[i] = 1;
            dfs(sum + a[i], dep + 1, i + 1);
            vis[i] = 0;
        }
    }
}
int main(){
    cin >> n >> k;
    a.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    dfs(0, 0, 0);
    cout << ans;
    return 0;
}