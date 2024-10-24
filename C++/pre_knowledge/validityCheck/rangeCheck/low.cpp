# include <iostream>
# include <string>
# include <limits>

/*std::cin 遇到错误（如类型不匹配）时，它会设置失败（fail）状态，
并可能导致程序进入无限循环或者停止后续的输入操作；
需要从 std::cin 读取多个值时，特别是在循环中读取时，
使用这两个函数（cin.clear(),cin.ignore()）来保证输入流的状态是干净的非常重要
*/

int main()
{
    int value;
    std::cout << "Please enter a number between 1 and 100 : ";
    
    while(!( std::cin >> value) || value < 0 || value > 100 )
    {
        std::cin.clear(); //清除输入流中的错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
         //忽略当前行剩余的输入，直到遇到换行符
        std::cout << "You entered a invalid number" << std::endl;
    }

    std::cout << "You entered a valid number : " << value << std::endl;

    return 0;
}