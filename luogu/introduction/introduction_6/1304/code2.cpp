#include <iostream>

const int N = 1e4 + 10;
int prime[N], st[N], cnt;

void init(int n) 
{
    st[0] = st[1] = 1;
    for (int i = 2; i <= n; ++i) 
    {
        if (!st[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] <= n / i; ++j) 
        {
            st[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() 
{
    init(1e4);
    int n;
    std::cin >> n;
    for (int i = 4; i <= n; i += 2) 
    {
        for (int j = 0; j < cnt; j++) 
        {
            if (prime[j] > i) break;
            if (!st[i - prime[j]]) 
            {
                std::cout << i << "=" << prime[j] << "+" << i - prime[j] << "\n";
                break; // 找到一组即可
            }
        }
    }
    return 0;
}
