#include <iostream>

#define max(a, b, c) a > b ? (c > a ? c : a) : (c > b ? c : b)
#define min(a, b, c) a < b ? (c < a ? c : a) : (c < b ? c : b)

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
//递归计算最大公约数, a / b = ....., 当 b == 0 时 返回最大公约数 a

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    int min = min(a, b, c);
    int max = max(a, b, c);

    int t = gcd(max, min);

    std::cout << min / t << "/" << max / t;
    return 0;
}