/*
样例输入3：
5
0 2
1 1
2 8
3 4
4 5
样例输出3：
2 2 0
3 2 1
11 9 1
15 12 8
20 16 11*/
#include <iostream>
using namespace std;
int n, t;
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int m, b;
        cin >> m >> b;
        cout << max(m, t) + b << " " << max(m, t) + b - m << " " << max(m, t)- m << endl;
        t = max(m, t) + b;
    }
    return 0;
}
