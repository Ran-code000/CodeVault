/*检查字符串是否可以转换为一个有效的整数并且这个整数是否在某个特定的范围内*/
/*cin.clear(),cin.ignore()两函数没用到，因为是从字符串进行转换，不是直接从std::cin输入*/

# include <iostream>
# include <string>
# include <limits>
# include <stdexcept>

bool isIntegerInrange( const std::string& str, int lowerBound, int upperBound )
{
    try
    {
        int value = std::stoi(str);
        return value >= lowerBound && value <=upperBound;

    }
    catch( const std::invalid_argument& ia )
    {
        std::cerr << "Invalid arguement" << ia.what() << std::endl;

    }
    catch( const std::out_of_range& oor)
    {
        std::cerr << "Out of range" << oor.what() << std::endl;
    }
    return false;
}

int main()
{
    std::string input;
    std::cout << "Enter a integer between 1 and 100 :  ";
    std::cin >> input;

    if(isIntegerInrange( input, 1, 100))
    {
        std::cout << "Valid integer within range : " << input << std::endl;
    }else
    {
        std::cout << "Invalid integer or not within range " << std::endl;
    }

    return 0;
}
/*此代码段假设用户的输入格式正确，且只包含整数，
在实际应用中，通常需要更健壮的错误检查和处理逻辑，见high.cpp*/

/*常见的类函数：

1.std::string 类：
size() 或 length(): 返回字符串的长度。
empty(): 检查字符串是否为空。
substr(): 获取字符串的一个子串。
append(), operator+=: 用于拼接字符串。
find(): 在字符串中查找子串或字符。
compare(): 比较两个字符串。

2.std::numeric_limits 类：
max(): 返回类型能表示的最大值。
min(): 返回类型能表示的最小值。
lowest(): 对于浮点类型，返回能表示的最低值。
epsilon(): 返回类型的epsilon值，即表示1和比1大的最小浮点数之间的差。
std::stdexcept 类的异常与作用
std::invalid_argument: 用于报告无效参数的异常。
std::out_of_range: 当操作尝试访问超出有效范围的元素时抛出。
std::runtime_error: 通用的运行时异常。*/