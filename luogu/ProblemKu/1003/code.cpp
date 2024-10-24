#include <iostream>
#include <vector>
using namespace std;
struct node{int a, b, x, y;};
int n, X, Y, last_id = -1;
vector<node> v;
int main(){
    cin >> n;
    int aa, bb, cc, dd;
    while(n-- && cin >> aa >> bb >> cc >> dd) v.push_back({aa, bb, cc, dd});
    cin >> X >> Y;
    for(int i = v.size() - 1; i >= 0; i--) if(v[i].a + v[i].x >= X && X >= v[i].a && v[i].b + v[i].y >= Y && Y >= v[i].b) {last_id = i; break;}
    cout << (last_id != -1 ? last_id + 1 : -1);
    return 0;
}