#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    int cnt1 = 0, cnt2 = 0;

    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == 'b')
        {
            cnt1++;
            s[i] = 'x';
            if(s[i+1] == 'o')
            {
                s[i+1] = 'x';
                if(s[i+2] == 'y')
                {
                    s[i+2] = 'x';
                }
            }
        }

        if(s[i] == 'o')
        {
            cnt1++;
            s[i] = 'x';
            if(s[i+1] == 'y')
            {
                s[i+1] = 'x';
            }
        }

        if(s[i] == 'y')
        {
            cnt1++;
        }
    }

    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == 'g')
        {
            cnt2++;
            s[i] = 'x';
            if(s[i+1] == 'i')
            {
                s[i+1] = 'x';
                if(s[i+2] == 'r')
                {
                    s[i+2] = 'x';
                    if(s[i+3] == 'l')
                    {
                        s[i+3] = 'x';
                    }
                }
            }
        }

        if(s[i] == 'i')
        {
            cnt2++;
            s[i] = 'x';
            if(s[i+1] == 'r')
            {
                s[i+1] = 'x';
                if(s[i+2] == 'l')
                {
                    s[i+2] = 'x';
                }
            }
        }

        if(s[i] == 'r')
        {
            cnt2++;
            s[i] = 'x';
            if(s[i+1] == 'l')
            {
                s[i+1] = 'x';
            }
        }

        if(s[i] == 'l')
        {
            cnt2++;
        }
    }

    std::cout << cnt1 << "\n" << cnt2;
    
    return 0;


}