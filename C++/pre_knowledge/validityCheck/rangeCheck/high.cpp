/*为了增强输入的错误检查和处理逻辑，做以下改进：
1.验证输入是否仅包含数字（和可能的负号），并给出适当的提示。
2.确保用户输入不为空。
3.处理用户输入后未处理的字符。
4.提供重试机制，允许用户在输入错误时重新输入。*/
# include <iostream>
# include <string>
# include <limits>
# include <cctype>
# include <stdexcept>

bool isIntegerInRange( const std::string& str, int lowerBound , int upperBound)
{
    if(str.empty())
    {
        return false;
    }

    size_t start = (str[0] == '-') ? 1 : 0;
    for(int i = start ; i < str.size() ; i++)
    {
        if(!isdigit(str[i])) return false;
    }

    try
    {
        int value = std::stoi(str);
        return value >= lowerBound && value <= upperBound;

    }
    catch(const std::invalid_argument& ia)
    {
        std::cerr << "Invalid arguement" << ia.what() << std::endl;

    }
    catch(const std::out_of_range& oor)
    {
        std::cerr << "Out of range" << oor.what() << std::endl;

    }
    return true;
    
}

int main()
{
    while(true)
    {
        std::string input;
        std::cout << "Enter a number between -100 and 100 :";
        
        if(!std::getline(std::cin,input))
        //getline可以包含空格的输入；
        {
            std::cerr << "Error reading input" << std::endl;
            return 1;
        }

        std::cin.clear();

        if(isIntegerInRange(input,-100,100))
        {
            std::cout << "You enter a valid number : " << input << std::endl;
            break;
        }else
        {
            std::cout << "You enter a invalid number !!!" << std::endl;
            std::cout << "Press enter to get restart" << std::endl;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    }
    return 0;
}

