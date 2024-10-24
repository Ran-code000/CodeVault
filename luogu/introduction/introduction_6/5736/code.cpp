#include <iostream>
#include <vector>
#include <cmath>

bool isPrime(int num)
{
    if(num <= 1)
    {
        return false;
    }else if(num ==2)
    {
        return true;
    }else if(num % 2 == 0)
    {
        return false;
    }
    
    for(int i = 3; i <= sqrt(num); i += 2)
    {
        if(num % i == 0)
        {
            return false;
        }
    }

    return true;
    
}

void printNum(const std::vector<int> &v)
{
    for(auto it = v.begin(); it !=v.end(); it++)
    {
        std::cout << *it << " ";
    }
    /*for(const int &val : v)
    {
        std::cout << val << " ";
    }
    */
   std::cout << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> v;
    v.reserve(n); //预分配内存
    //避免了在 vector 初始化时就填充元素，而是根据输入动态地添加质数。
    //使用 reserve 方法来预留足够的空间，这样可以在输入很多数字时减少内存重新分配的次数，
    //但不会像初始化 vector<int> v(n) 那样填充不必要的元素。
    //std::vector<int> v;
    //v.reserve(n); //预分配内存

    for(int i=0; i<n; i++)
    {
        int num;
        std::cin >> num;

        if(isPrime(num))
        {
            v.push_back(num);
        }

    }

    printNum(v);

    return 0;
}