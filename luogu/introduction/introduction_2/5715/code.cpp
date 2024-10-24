#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec;
    int a, b, c;
    std::cin >> a >> b >> c;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);

    std::sort(vec.begin(), vec.end());

    for(int val : vec)
    {
        std::cout << val << " ";

    }

    return 0;
}