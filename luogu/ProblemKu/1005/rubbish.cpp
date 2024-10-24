#include <iostream>
#include <cmath>
using namespace std;
int n, m;
long long res;
int main(){
    cin >> n >> m;
    while(n--){
        int a[m], j = 0, k = m - 1, id = 1;
        long long sum = 0;
        for(int i = 0; i < m; i++) cin >> a[i];
        while(j <= k){
            if(a[j] >= a[k]) sum += a[k] * (int)pow(2, id), k--;
            else if(a[j] < a[k]) sum += a[j] * (int)pow(2, id), j++;
            id++;
        }
        res += sum;
    }
    cout << res;
    return 0;
}