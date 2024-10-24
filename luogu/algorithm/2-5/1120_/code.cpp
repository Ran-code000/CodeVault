#include <iostream>
using namespace std;
//四步优化（桶的优化，从大到小遍历，取出所有可能性，下一次遍历最大所需长度）
//57 分
int n, len, max_len, min_len = 100, a[51], b[70], j;//b[] 可拼的因数(木棍长度)
//dfs(需要拼的总长度， 拼了几个木棍， 当前木棍的长度， 当前拼的木棍的长度(从最长的开始拼，优化))
void dfs(int sum_len, int dep, int current_len, int start_max_len){
    if(dep == n){
        //可以用全部木棍拼成若干个 sun_len 长度的木棍
        cout << sum_len;
        exit(0);//直接退出程序
    }
    if(current_len == sum_len){
        //拼好一个木棍，更新
        current_len = 0;//开始拼下一个
        start_max_len = max_len;//从最大的开始拼
    }
    for(int i = start_max_len; i >= min_len; i--){
        //遍历可能木棍长度
        if(!a[i]) continue;//判断是否存在该长度的木棍
        a[i]--;
        //两种情况
        //100   30 29 28 27 ----- min() = 30
        //8   1 1 1 2 2 3 3 3 5 5 ---- min() = 8 - 5 = 3;
        dfs(sum_len, dep + 1, current_len + i, min(i, sum_len - (current_len + i)));
        a[i]++;//回溯
        //8   5 2 2 2 2 拼完 5 2 找 1 找不到，回溯继续尝试 2 没有意义
        if(current_len == 0) break;//第五步优化，搜完一遍还一个都没有拼就尝试下一个，不对 //78
        //6   5 4 1 1 1 已经拼成 5 1 ，回溯继续尝试后面的 1 没有意义
        if(current_len + i == sum_len) break;//第六步优化，已经拼成没必要再找后面的 //100
        //不同于循环外的判断
    }
    return;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        //装桶优化
        //利用已经分类的桶来快速决定哪些长度的木棍是可用的，而无需遍历所有可能的长度，可以通过跳过数量为0的桶实现
        int x;
        cin >> x;
        a[x]++;
        max_len = max(max_len, x);
        min_len = min(min_len, x);
        len += x;//len 为木棍总长度
    }
    //9   5 2 1 5 2 1 5 2 1
    //从最大长度开始遍历，可以拼的木棍的长度必定是总长度的因数
    for(int i = max_len; i <= len / 2; i++) if(len % i == 0) b[j++] = i;
    //for(int i = 0; i < j; i++) cout << b[i] << " ";
    //dfs 每个因数是否成功拼成木棍
    for(int i = 0; i < j; i++) dfs(b[i], 0, 0, max_len);
    cout << len;
    return 0;
}