#include <iostream>
#include <set>
using namespace std;
int n, m, a[200000], b[200000], btop = 1;
multiset<int> tree;
multiset<int>::iterator it;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    it = tree.begin();
    for(int i = 1; i <= n; i++){
        tree.insert(a[i]);
        if(*it > a[i]) it--;
        while(b[btop] == i){
            cout << *it << endl;
            btop++;
            it++;
        }
    }
    return 0;
}