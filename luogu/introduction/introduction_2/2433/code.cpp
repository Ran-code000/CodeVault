#include <iostream>
#include <cmath>
#include <climits>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;

    int ans = 1;
    int arr[2];
    int cnt = 0;
    switch(n)
    {
        case 1:
            std::cout << "I love Luogu!";
            break;
        case 2:
            std::cout << 6 << " " << 4;
            break;
        case 3:
            std::cout << 3 << "\n" << 12 << "\n" << 2;
            break;
        case 4:
            std::cout << std::fixed << std::setprecision(3) << 500.0 / 3;
            break;
        case 5:
            std::cout << 15;
            break;
        case 6:
            std::cout << std::sqrt(pow(6, 2) + pow(9, 2));
            break;
        case 7:
            std::cout << 110 << "\n" << 90 << "\n" << 0;
            break;
        case 8:
            std::cout << 2 * 3.141593 * 5.0 << "\n" << 3.141593 * 25.0 << "\n" << 4.0 / 3 * 3.141593 * pow(5, 3);
            break;
        case 9:
            for(int i = 0; i < 3; i++)
            {
                ans = (ans + 1) * 2;
            }
            std::cout << ans;
            break;
        case 10:
            std::cout << 9;
            break;
        case 11:
            std::cout << 100.0 / 3;
            break;
        case 12:
            std::cout << 'M' - 'A' + 1 << "\n" << (char)('A' + 18 - 1);
            //若需要输出字符需要(char)
            break;
        case 13:
            for(int i = 1; i <= 100; i++)
            {
                double sum = 4.0 / 3 * 3.141593 * (pow(4, 3) + pow(10, 3));
                if(i * i * i >= sum)
                {
                    std::cout << (int)(i - 1);
                    break;
                }
            }
            break;
        case 14:
            for(int i = 1; i <= 110; i++)
            {
                int sum = ((110 - i) + 10) * i;
                if(sum == 3500)
                {
                    std::cout << i;
                    break;
                }
            }
            break;
    }
}