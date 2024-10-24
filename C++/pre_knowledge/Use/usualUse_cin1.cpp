# include <iostream>
//using namespace std ;

int main()
{
    int n;
    int sum=0;
    while( std::cin >> n)
    {
        sum+=n;
        while( std::cin.peek()==' ')
        //cin.peek()验证完返回到输出流
        {
            std::cin.get();
        }
        if(std::cin.peek()=='\n') break;
    }
    std::cout << sum << std::endl;
    return 0;
}