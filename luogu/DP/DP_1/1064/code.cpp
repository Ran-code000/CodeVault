/*
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0*/
#include <iostream>
//特殊条件限制的 01 背包
using namespace std;
struct node{
    int id, w, c, s, vis;
}a[32005];
int num_of_secondGoods[32005], dp[32005], W, n;
int main(){
    cin >> W >> n;
    for(int i = 1; i <= n; i++){
        int ww, cc, typee;
        cin >> ww >> cc >> typee;
        if(a[i].vis == 0) a[i].id = i, a[i].w = ww, a[i].s = ww * cc, a[i].vis = 0;
        else a[i].id = typee, a[i].w = ww, a[i].s = ww * cc, a[i].vis = ++num_of_secondGoods[typee];
    }
    sort(a + 1, a + )
    return 0;
}