#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned long long n;
    std::cin >> n;

    std::vector<unsigned long long> vec;
    vec.reserve(1e5 + 10);

    vec.push_back(n);

    while(1)
    {
        if(n % 2 == 0)
        {
            n /= 2;
            vec.push_back(n);
        }else
        {
            if(n == 1) break;
            n = n * 3 + 1;
            vec.push_back(n);
        }


    }

    std::reverse(vec.begin(), vec.end());

    for(const auto &val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}