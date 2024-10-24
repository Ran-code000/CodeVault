#include <iostream>
#include <set>//维护序列有序

using namespace std;
int n, m, a[200000], b[200000], btop = 1;
multiset<int> tree;//存储位置变，结构类似于链表，不能像数组一样访问
multiset<int>::iterator it;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    for(int i = 1; i <= n; i++){
        tree.insert(a[i]);
        //查询
        while(b[btop] == i){
            //注意用 while 不用 if，例如 b 数组为数据 1 2 6 6 时
            it = tree.begin();//每次需要从头遍历，太慢，优化 ———— 手写插入排序
            for(int j = 0; j < btop - 1; j++) it++;//it++ 可以，it + 5 不行，不是数组的这种联系存储
            cout << *it << "\n";
            btop++;
        }
    }
    return 0;
}