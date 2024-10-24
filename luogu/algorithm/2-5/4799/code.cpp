#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
// 0 分！！！！！只过了样例
using namespace std;
long long m, n, ans;
long long matrix[42][42];
vector<long long> a;

void init_pascals_triangle() {
    memset(matrix, 0, sizeof(matrix)); 
    for (int i = 0; i < 42; i++) {
        matrix[i][0] = matrix[i][i] = 1;
        for (int j = 1; j < i; j++) matrix[i][j] = matrix[i-1][j-1] + matrix[i-1][j];
    }
}
long long matrix_count(int x){
    long long summ = 0;
    for(int j = 1; j <= x; j++) summ += matrix[x][j];
    return summ;
}
int main() {
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    init_pascals_triangle();  //初始化杨辉三角

    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }*/
    int pos = 0;
    while (pos < n) {
        int cnt = 0;
        long long sum = 0;
        int i = pos;
        if(a[i] > m) break;
        while (i < n && sum + a[i] <= m) {
            sum += a[i++];
            cnt++;
        }
        if (cnt > 0) {  // 检查cnt是否大于0，再尝试访问matrix
            ans += matrix_count(cnt);  
        }
        pos++;  // 更新pos为下一个开始的位置
    }

    cout << ans << endl;
    return 0;
}
