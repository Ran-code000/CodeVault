# include <iostream>
# include <limits>
# include <climits>

class Factorial
{
public:
    Factorial(unsigned short number);
    unsigned long long getFactorial();
    bool inRange();

private:
    unsigned short number;
};

Factorial::Factorial(unsigned short number)
{
    this ->number = number;
}

unsigned long long  Factorial::getFactorial()
{
    unsigned long long sum = 1;

    for(int i = 1 ; i <=number ; i++)
    {
        sum *= i;
    }

    return sum;
}

bool Factorial::inRange()
{
    unsigned long long max = ULLONG_MAX;

    for( int i = number ; i>=1 ; i--)
    {
        max/=i;
    }

    if(max < 1)
    {
        return false;
    }else
    {
        return true;
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
        Factorial fac(number);

        if( fac.inRange())
        {
            std::cout << "阶乘的结果是 : " << fac.getFactorial() << "\n";
        }else
        {
            std::cerr << "您输入的值过大" << "\n";
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

