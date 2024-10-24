#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> vec(n);
    int min = INT_MAX;

    for(int i = 0; i < vec.size(); i++)
    {
        std::cin >> vec[i];
        if(vec[i] < min) min = vec[i];
    }

    std::cout << min << std::endl;

    return 0;

}