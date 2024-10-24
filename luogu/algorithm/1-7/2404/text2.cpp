#include <iostream>
#include <vector>

using namespace std;
int n;
vector<int> a;
void dfs(int sum, int start){
    if(sum > n) return;
    if(sum == n){
        for(int i = 0; i < a.size() - 1; i++) cout << a[i] << "+";
        cout << a[a.size() - 1] << "\n";
        return;
    }
    for(int i = start;  i <= n - 1; i++){
        a.push_back(i);
        dfs(sum + i, i);
        a.pop_back();
    }
}
int main(){
    cin >> n;
    dfs(0, 1);
    return 0;
}