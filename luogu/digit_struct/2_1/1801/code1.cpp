#include <iostream>
#include <set>//维护序列有序
#include <cstring>//用到 memcpy
#include <algorithm>
using namespace std;
int n, m, a[200000], b[200000], btop = 1, pos;
int tree[200005];//插入排序数组
//multiset<int>::iterator it;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    for(int i = 1; i <= n; i++){
        //tree.insert(a[i]);
        //用 memcpy 手写插入排序
        if(i == 1) tree[i] = a[i];
        else{
            pos = upper_bound(tree + 1, tree + i, a[i]) - tree;//找到第一个比 a[i] 大的数的位置索引
            if(pos == i) tree[i] = a[i];//加的数即为最大值，直接填
            else{
                memcpy(tree + pos + 1, tree + pos, sizeof(int) * (i - pos));//移动内存
                tree[pos] = a[i];//填空位
            }  
        } 
        //查询
        while(b[btop] == i){
            //注意用 while 不用 if，例如 b 数组为数据 1 2 6 6 时
            // it = tree.begin();//每次需要从头遍历，太慢，优化 ———— 手写插入排序，见 code1.cpp
            //for(int j = 0; j < btop - 1; j++) it++;//it++ 可以，it + 5 不行，不是数组的这种联系存储
            cout << tree[btop] << "\n";
            btop++;
        }
    }
    return 0;
}