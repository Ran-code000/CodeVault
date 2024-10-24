#include <iostream>
#include <string>

int main()
{
    std::string str, temp;
    std::cin >> str;

    for(int i = 0; i < str.length() - 1; i++)
    {
        if(str[i] >= '0' && str[i] <= '9') temp += str[i];
    }

    int sum = 0;
    for(int i = 0; i < temp.length(); i++)
    {
        sum += (temp[i] - '0') * (i + 1);
    }

    std::string ans = sum % 11 == 10 ? "X" : std::to_string(sum % 11); 
    if(ans[0] == str[str.length() - 1])
    {
        std::cout << "Right";
    }else
    {
        temp.clear();
        temp += str.substr(0, str.length() - 1);
        temp += ans;
        std::cout << temp;
    }

    return 0;
    
}