# include <iostream>
# include <limits>
 
int main()
{
    char answer;
    std::cout << "请问可以格式化您的硬盘吗【Y/N】" << std::endl;
    std::cin >> answer;

    switch( answer )
    {
        case'Y':
        case'y':
            std::cout <<"不要随意格式化硬盘" << std::endl;
            break;
        case'N':
        case'n':
            std::cout <<"您的选择正确" << std::endl;
            break;
        default:
            std::cout <<"输入错误!!!!!" << std::endl;
            break;
    }
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << "输入任何字符结束程序" << std::endl;
    std::cin.get();
    return 0;
    
}