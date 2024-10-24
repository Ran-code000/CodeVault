#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream> //stringstream l(s);

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::string s;

    int op[55];

    for(int i=0; i<n; i++)
    //比用while(n--)更好,因为可以用i来控制每一行
    {
        std::getline(std::cin,s);
        std::stringstream l(s);

        std::string str;
        std::vector<std::string> vec;
        while(l>>str)
        {
            vec.push_back(str);
        }

        int temp1=0,temp2=0;

        if(vec.size() == 2)
        {
            temp1 = stoi(vec[0]);
            temp2 = stoi(vec[1]);
            op[i] = op[i-1];

        }else
        {
            temp1 = stoi(vec[1]);
            temp2 = stoi(vec[2]);
            op[i] = vec[0][0] - 'a';
        } 

        if(op[i] == 0)
        {
            int t = temp1 + temp2;
            std::string ans;
            ans += std::to_string(temp1) + "+" + std::to_string(temp2) + "=" + std::to_string(t);

            std::cout << ans << std::endl;
            std::cout << ans.size() << std::endl;
        }

        if(op[i] == 1)
        {
            int t = temp1 - temp2;
            std::string ans;
            ans += std::to_string(temp1) + "-" + std::to_string(temp2) + "=" + std::to_string(t);

            std::cout << ans << std::endl;
            std::cout << ans.size() << std::endl;
        }

        if(op[i] == 2)
        {
            int t = temp1 * temp2;
            std::string ans;
            ans += std::to_string(temp1) + "*" + std::to_string(temp2) + "=" + std::to_string(t);

            std::cout << ans << std::endl;
            std::cout << ans.size() << std::endl;
        }

    
    }

    return 0;
}