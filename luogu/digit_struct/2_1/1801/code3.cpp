#include <iostream>
#include <queue>//需要大根堆和小根堆
//堆顶堆（上 ———— 小根堆， 下 ———— 大根堆）的数据结构优化（数从下向上 ———— 从小到大）———— 序列动态，问第几小（大）
using namespace std;
priority_queue<int> qb;//大根堆
priority_queue<int, vector<int>, greater<int>> qs;//小根堆
int n, m, a[200000], b[200000], btop = 1;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);//cin >> a[i];
    for(int i = 1; i <= m; i++) scanf("%d", &b[i]);//cin >> b[i];
    for(int i = 1; i <= n; i++){
        qb.push(a[i]);//先放大根堆中 ———— 因为题目要求的是第几小的
        //询问
        while(b[btop] == i){
            while(qb.size() > btop){
                qs.push(qb.top());
                qb.pop();
            }
            //cout << qb.top() << "\n";
            printf("%d\n", qb.top());
            if(!qs.empty()){
                qb.push(qs.top());
                qs.pop();
            }
            btop++;
        }
    }
    return 0;
}