#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::map<char, int> m;
    std::vector<int> vec(3);

    for(int i = 0; i < 3; i++)
    {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    m['A'] = vec[0];
    m['B'] = vec[1];
    m['C'] = vec[2];

    for(int i = 0; i < 3; i++)
    {
        char x;
        std::cin >> x;
        std::cout << m[x] << " ";
    }

    return 0;
}
