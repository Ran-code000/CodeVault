#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    std::string str;
    std::cin >> str;

    auto begin_it = str[0] == '-'? str.begin() + 1 : str.begin();
    
    int endIndex = str.length() - 1;

    while(str[endIndex] == '0')
    {   
        endIndex--;
    }
    if(endIndex < 0)
    {
        std::cout << 0;
        return 0;
    }

    auto end_it = str.begin() + endIndex + 1;
    std::reverse(begin_it, end_it);

    for(int i = 0; i <= endIndex; i++)
    {
        std::cout << str[i]; 
    }

    return 0;


}