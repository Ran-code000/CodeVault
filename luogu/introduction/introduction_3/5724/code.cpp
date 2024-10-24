#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> vec(n);

    for(int i = 0; i < n; i++)
    {
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end());

    std::cout << vec[vec.size() - 1] - vec[0] << std::endl;

    return 0;
}