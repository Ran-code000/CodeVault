#include <iostream>
#include <string>
#include <cstring>

int main()
{
    int n;
    std::cin >> n;

    std::string ss;
    std::cin >> ss;

    while(n--)
    {
        int num;
        std::cin >> num;

        std::string s1,s2,s3;
        int a,b;
        int t;
        std::string temp1,temp2;
        int index;

        switch (num)
        {
            case 1 :
                std::cin >> s1;
                ss += s1;

                std::cout << ss << std::endl;
                break;

            case 2 :
                std::cin >> a >> b;

                ss = ss.substr(a,b);
                std::cout << ss << std::endl;
                break;

            case 3 :
                
                std::cin >> t >> s2;
                
                ss = ss.insert(t,s2);

                std::cout << ss << std::endl;
                break;

            case 4 :
                
                std::cin >> s3;
                if(ss.find(s3) != std::string::npos)
                {
                    index = ss.find(s3);
                    std::cout << index << std::endl;
                }else
                {
                    std::cout << -1 << std::endl;
                }
                break;

            default:
                break;
                
        }
    }
    return 0;
}