// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;
namespace jyy{
	const int mod=1e9+7,N=200010;
	const double eps=1e-8;
	#define ll long long
	inline int read(){
		static int x=0,f=1;x=0,f=1;
		static char ch=getchar();
		while(ch<'0'||ch>'9'){(ch=='-')?f*=-1:f;ch=getchar();}
		while(ch>='0'&&ch<='9')x=x*10+int(ch-48),ch=getchar();
		return x*f;
	}
	inline void fw(int x){if(x<0)putchar('-'),x=-x;x>=10?fw(x/10),1:0;putchar(char(x%10+48));}
	int qmo(int x){return x+((x>>31)&mod);}
	int ksm(int x,int y){
		if(y<0)return 0;
	int tmp=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)tmp=1ll*tmp*x%mod;return tmp;}
	int inv(int x){return ksm(x,mod-2);}
	int tot,head[N],fa[N];
	struct edge{int to,next;}dat[N*2];
	void add_edge(int x,int y){dat[++tot]=(edge){y,head[x]},head[x]=tot;}
	int find(int x){return fa[x]?fa[x]=find(fa[x]):x;}
	void merge(int x,int y){find(x)!=find(y)?fa[find(x)]=find(y):0;}
	int low(int x){return x&-x;}
	int ifac[N],fac[N];
	void init(int x){fac[0]=ifac[0]=1;for(int i=1;i<=x;i++)fac[i]=1ll*fac[i-1]*i%mod;ifac[x]=inv(fac[x]);for(int i=x-1;i>=1;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;}
	int c(int x,int y){return (x<y||y<0||x<0)?0:1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;}
}
using namespace jyy;
int dp[N][2];
void solve(){
	int n=read(),ans=0;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)dp[i][0]=qmo(dp[i-1][0]+dp[i-1][1]-mod),dp[i][1]=dp[i-1][0];
	for(int i=1;i<=n;i++){
		int x=read();
		if(i==1)ans=qmo(ans+1ll*(dp[n-1][0]+dp[n-1][1])*x%mod-mod);
		else{
			ans=qmo(ans+1ll*(dp[i-2][0]+dp[i-2][1])*(dp[n-i][0]+dp[n-i][1])%mod*x%mod-mod);		
			ans=qmo(ans-1ll*(dp[i-2][0])*dp[n-i][0]%mod*x%mod);
		}
	}
	cout<<ans;
}
int T;
int main(){
	if(0)cin>>T;
	else T=1;
	while(T--)solve();
}
