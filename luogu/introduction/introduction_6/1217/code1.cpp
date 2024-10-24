#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

//38ms
//88分，优化代码见code2.cpp

bool isPrime(int n);
int judgeDigit(int n);
void getNumber(int a, int du, int b, std::vector<int> &ans);

int main()
{
    int a, b;
    std::cin >> a >> b;
    int digitupper = judgeDigit(b);

    std::vector<int> ans;
    ans.reserve(3000);

    getNumber(a, digitupper, b, ans);

    return 0;
}

bool isPrime(int n)
{
    if(n == 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i++)
    {
        if(n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int judgeDigit(int n)
{
    if(n > 0 && n < 10) return 1;

    int cnt = 1;

    while(1)
    {
        n /= 10;
        cnt++;

        if(n > 0 && n < 10) break;   
    }

    return cnt;
}

void getNumber(int a, int du, int b, std::vector<int> &ans)
{
    int t = 9 - du;
    switch(t)
    {
        case 1: 
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    for(int a3 = 0; a3 <= 9; a3++)
                    {
                        for(int a4 = 0; a4 <= 9; a4++)
                        {
                            int sum = a1 * 1E7 + a2 * 1E6 + a3 * 1E5 + a4 * 1E4 + a4 * 1E3 + a3 * 1E2 + a2 * 10 + a1;
                            if(sum >= a && sum <=b && isPrime(sum))
                            {
                                ans.push_back(sum);
                            }
                        }
                    }
                }
            }
        case 2:
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    for(int a3 = 0; a3 <= 9; a3++)
                    {
                        for(int a4 = 0; a4 <= 9; a4++)
                        {
                            int sum = a1 * 1E6 + a2 * 1E5 + a3 * 1E4 + a4 * 1E3 + a3 * 1E2 + a2 * 10 + a1;
                            if(sum >= a && sum <=b && isPrime(sum))
                            {
                                ans.push_back(sum);
                            }
                        }
                    }
                }
            }
        case 3:
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    for(int a3 = 0; a3 <= 9; a3++)
                    {
                        int sum = a1 * 1E5 + a2 * 1E4 + a3 * 1E3 + a3 * 1E2 + a2 * 10 + a1;
                        if(sum >= a && sum <=b && isPrime(sum))
                        {
                            ans.push_back(sum);
                        }
                    }
                }
            }
        case 4:
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    for(int a3 = 0; a3 <= 9; a3++)
                    {
                        int sum = a1 * 1E4 + a2 * 1E3 + a3 * 1E2 + a2 * 10 + a1;
                        if(sum >= a && sum <=b && isPrime(sum))
                        {
                            ans.push_back(sum);
                        }
                    }
                }
            }
        case 5:
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    int sum = a1 * 1E3 + a2 * 1E2 + a2 * 10 + a1;
                    if(sum >= a && sum <=b && isPrime(sum))
                    {
                        ans.push_back(sum);
                    }
                }
            }
        case 6:
            for(int a1 = 1; a1 <= 9; a1+=2)
            {
                for(int a2 = 0; a2 <= 9; a2++)
                {
                    int sum = a1 * 1E2 + a2 * 10 + a1;
                    if(sum >= a && sum <=b && isPrime(sum))
                    {
                        ans.push_back(sum);
                    }
                }
            }
        case 7:
            if(a <= 11) 
            {
                ans.push_back(11);
            }
        case 8:
            if(a <= 7)
            {
                ans.push_back(7);
            }
            if(a == 5) ans.push_back(5);
    }
    std::sort(ans.begin(), ans.end());

    for(const auto &val : ans)
    {
        std::cout << val << "\n";
    }
    std::cout << std::endl;
}