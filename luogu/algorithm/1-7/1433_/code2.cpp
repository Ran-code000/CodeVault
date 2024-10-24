#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std;
double dis[21][21];//预处理，从第i块到第j块的距离，使用两点之间距离公式 
double a[21][2];//每块奶酪的横、纵坐标
double dp[18][34000];//状压DP数组 在第i个点上，走过的二进制状态的十进制表达为j时，最短的距离 
int n; 
double distance(int i,int j){
	double r1 = a[i][0] - a[j][0];
    double r2 = a[i][1] - a[j][1];
    return sqrt(r1 * r1 + r2 * r2);
}
int main(){
	double ans;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];//数据读入 
    a[0][0] = a[0][1] = 0;
	for(int i = 0; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			dis[i][j] = distance(i,j);//初始化距离数组 
			dis[j][i] = dis[i][j];
		}
	} 
	for(int i = 1; i <= n; i++) dp[i][1 << (i - 1)] = dis[0][i];//在i点上且只有经过i点时距离是原点到i点的距离 
    //枚举所有二进制状态(路径)
	for(int k = 1; k < (1 << n); k++){
		for(int i = 1; i <= n; i++){
			if((k & (1 << (i - 1))) == 0) continue;//i的位置没被走过，所以不需要再继续计算了 
			for(int j = 1; j <= n; j++){
				if(i == j) continue;//同一个点不需要再计算 
				if((k & (1 << (j - 1))) == 0) continue;//j的位置没走过  
				dp[i][k] = min(dp[i][k], dp[j][k - ( 1 << (i - 1))] + dis[i][j]);
			}  
		} 
	} 
	for(int i = 1; i <= n; i++) ans = min(ans, dp[i][(1 << n) - 1]);
	cout << fixed << setprecision(2) << ans;
    return 0;
}
