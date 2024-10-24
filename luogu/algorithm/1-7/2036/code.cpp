#include <iostream>
#include <cmath>

using namespace std;
int n, a[11], b[11], vis[11], mul = 1, sum = 0, minn = 0x3f3f3f;

void dfs(int mul, int sum){
    //跳过起始点，类比2392
    if(!(mul == 1 && sum == 0) && abs(mul - sum) < minn) minn = abs(mul - sum);
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            vis[i] = 1;
            dfs(mul * a[i], sum + b[i]);
            vis[i] = 0;
        }
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
    dfs(1, 0);
    cout << minn;
    return 0;
}
