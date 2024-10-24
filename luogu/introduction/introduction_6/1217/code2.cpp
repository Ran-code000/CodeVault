#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

//563ms
//回文数判断(palindrome) 和质数(prime) 判断
//注意判断的先后顺序, 回文数少质数多, 先判断回文数, 否则可能导致超时
//观察题目做优化,去掉所有正偶数时间少一半

bool isPrime(int n)
{
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i+=2)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool isPalindrome(int n)
{
    int original = n, reversed = 0;
    while(n > 0)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}

std::vector<int> getPalindromePrime(int a, int b)
{
    std::vector<int> ans;
    for(int i = a; i <= b; i++)
    {
        if(i % 2 == 0) continue;
        if(isPalindrome(i) && isPrime(i))
        //注意判断的先后顺序, 回文数少质数多, 先判断回文数, 否则可能导致超时
        {
            ans.push_back(i);
        }
    }
    return ans;
}


int main()
{
    int a, b;
    std::cin >> a >> b;

    auto ans = getPalindromePrime(a, b);

    for(const auto &val : ans)
    {
        std::cout << val << "\n";
    }
    std::cout << std::endl;

    return 0;
}