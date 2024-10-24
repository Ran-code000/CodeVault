#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> vec(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> vec[i];
    }

    int max = -1;
    for(int i = 0; i < n; i++)
    {   
        int j = i; 
        while(vec[j + 1] == vec[j] + 1) j++;
        if(j - i + 1 > max) max = j - i + 1;
        i = j;
    }

    std::cout << max;
    return 0;
}