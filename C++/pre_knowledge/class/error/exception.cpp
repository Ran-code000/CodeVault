# include <iostream>
# include <limits>
# include <climits>

//面向过程的方法，用到try catch,本例用的指针，若打算使用对象作为异常，需要用值传递抛出对象，引用传递捕获对象，
//详见validityCheck_rangeCheck_high.cpp

unsigned long long  returnFactorial(unsigned short number) //throw (const *char)
{
    unsigned long long sum = 1;
    unsigned long long max = ULLONG_MAX;

    for(int i = 1 ; i <=number ; i++)
    {
        sum *= i;
        max/=i;
    }

    if(max < 1)
    {
        throw "您输入的值过大!!!";
    }else
    {
        return sum;
    }
}

int main()
{
    unsigned short number = 0;

    while(1)
    {
        std::cout << "请输入一个整数 : ";
        
        while(!(std::cin >> number))
        {
            if(number > USHRT_MAX)
            {
                std::cerr << "您输入的值过大" << "\n";
            }else
            {
                std::cerr << "输入不合法，请重新输入" << "\n";
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            
            std::cout << "请输入一个整数 : ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        try
        {
            unsigned long long factorial = returnFactorial(number);
            std::cout << "阶乘的结果是 : " << factorial << "\n";
        }
        catch(const char *e) //用指针接收
        {
            std::cerr << e << '\n';
        }
        
        char choice;

        std::cout << "是否继续？(Y/N) : ";
        
        while(1)
        {
            while(!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cerr << "输入不合法，请重新输入" << "\n";
        }
        if( toupper(choice) == 'N')
        {
            return 0;
        }else if( toupper(choice) == 'Y')
        {
            break;
        }else
        {
            std::cerr << "未输入合适字母，请重新输入" << "\n";
            std::cout << "输入(Y/N)";
        }

        }
        
    }

    return 0;
}

