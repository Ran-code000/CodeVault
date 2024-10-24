#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
int n, k, sum = 0, cnt = 0;
vector<int> s, ans, vis;

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
        /*for(int i = 0; i < dep ; i++){
            cout << ans[i] << " ";
        }cout << "\n";*/
        return;
        //return可以使递归函数的逻辑更加清晰和直观。它清楚地表明一旦一个长度为k的组合被处理（无论是否是素数和）
        //，就不再需要继续当前的递归路径。
    }
    //用 sort 保证升序，从而用 start 保证每次搜索的值都比上一次搜索的值大
    for(int i = start; i < n; i++){
        if(!vis[i]){
            vis[i] = 1;
            sum += s[i];
            ans.push_back(s[i]);
            dfs(dep + 1, i + 1); //修正起始索引和递归调用
            //恢复所有状态
            vis[i] = 0;
            ans.pop_back();
            sum -= s[i];
        }
    }
}

int main(){
    cin >> n >> k;
    s.resize(n);
    vis.resize(n);
    //ans.resize(n);这行代码实际上是多余的，并且可能会导致逻辑错误。ans应该被用作动态数组
    //（即利用push_back和pop_back来管理元素），因此初始化时不应该设定大小。由于resize导致ans的大小预先被设置为n，
    //在打印时即便ans还没有被完全填满，也会根据其当前大小打印，这就是为什么你看到了多个0的输出
    for(int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end()); //保证元素升序
    dfs(0, 0);
    cout << cnt;
    return 0;
}