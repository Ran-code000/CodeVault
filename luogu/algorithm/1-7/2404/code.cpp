#include <iostream>
#include <vector>

using namespace std;
int n;
vector<int> ans;

void dfs(int sum, int start){
    if(sum > n) return; 
    if(sum == n){
        for(int i = 0; i < ans.size() - 1; i++) cout << ans[i] << "+";
        cout << ans[ans.size() - 1] << "\n";
        return;
    }
    for(int i = start; i <= n - 1; i++){
        ans.push_back(i); //保存路径 类比2306
        dfs(sum + i, i);
        ans.pop_back(); //回溯
    }
}

int main(){
    cin >> n;
    dfs(0, 1);
    return 0;
}