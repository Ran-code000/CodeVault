#include <iostream>

int main()
{
    int n,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9;
    int cnt=0;
    
    std::cin >> n;

    if(n > 30 || n < 10)
    {
        std::cout << 0;
        return 0;
    }

    for(int a0=1; a0<=3; a0++)
    {
        for(int a1=1; a1<=3; a1++)
        {
            for(int a2=1; a2<=3; a2++)
            {
                for(int a3=1; a3<=3; a3++)
                {
                    for(int a4=1; a4<=3; a4++)
                    {
                        for(int a5=1; a5<=3; a5++)
                        {
                            for(int a6=1; a6<=3; a6++)
                            {
                                for(int a7=1; a7<=3; a7++)
                                {
                                    for(int a8=1; a8<=3; a8++)
                                    {
                                        for(int a9=1; a9<=3; a9++)
                                        {
                                            if(a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 == n)
                                            {
                                                cnt++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << cnt << std::endl;

    for(int a0=1; a0<=3; a0++)
    {
        for(int a1=1; a1<=3; a1++)
        {
            for(int a2=1; a2<=3; a2++)
            {
                for(int a3=1; a3<=3; a3++)
                {
                    for(int a4=1; a4<=3; a4++)
                    {
                        for(int a5=1; a5<=3; a5++)
                        {
                            for(int a6=1; a6<=3; a6++)
                            {
                                for(int a7=1; a7<=3; a7++)
                                {
                                    for(int a8=1; a8<=3; a8++)
                                    {
                                        for(int a9=1; a9<=3; a9++)
                                        {
                                            if(a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 == n)
                                            {
                                                std::cout << a0 << " " << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << " " << a7 << " " << a8 << " " << a9 << "\n";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}