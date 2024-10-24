#include <iostream>
#include <iomanip>

int main()
{
    int n, k;
    std::cin >> n >> k;

    int sum1 = 0, cnt1 = 0;;
    int sum2 = 0, cnt2 = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i % k) 
        {
            sum2 += i;
            cnt2++;
        }else
        {
            sum1 += i;
            cnt1++;
        }
        
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << (double)sum1 / cnt1 << " " << (double)sum2 / cnt2 << std::endl;

    return 0;
}