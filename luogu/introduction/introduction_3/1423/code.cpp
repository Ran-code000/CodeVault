#include <iostream>

int main()
{
    double s;
    std::cin >> s;

    double t = 2, sum = 0;
    int cnt = 1;

    while(1)
    {
        sum += t;
        t *= 0.98;
        if(sum >= s) break;
        cnt++;
        
    }
    std::cout << cnt;

    return 0;
}