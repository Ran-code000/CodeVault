#include <iostream>
#include <vector>

using namespace std;
int n;
vector<int> ans;

void dfs(int dep, int sum, int start){
    if(sum > n) return;
    if(sum == n ){
        cout << n << "=";
        //搜多少查多少
        for(int i = 0; i < dep - 1; i++) cout << ans[i] << "+";
        cout << ans[dep - 1] << "\n";//特判
        return;
    }
    for(int i = start; i <= n - 1; i++){
        ans.push_back(i);
        dfs(dep + 1, sum + i, i);
        ans.pop_back();//回溯
    }
}

int main(){
    cin >> n;
    dfs(0, 0, 1);
    return 0;
}