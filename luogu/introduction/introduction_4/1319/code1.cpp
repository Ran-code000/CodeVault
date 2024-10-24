#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    int cnt = 0;
    int sum = 0;
    std::string temp;
    while(1)
    {
        cnt++;
        int x;
        std::cin >> x;

        for(int i = 0; i < x; i++)
        {
            if(cnt % 2)
            {
                temp += "0";
            }else
            {
                temp += "1";
            }
        }

        sum += x;
        if(sum == n * n) break;
    }

    for(int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i];
        if((i + 1) % n == 0 && i != 0) std::cout << "\n";
    }
    
    return 0;
}