# include <iostream>
# include <string>

/*print 函数根据传入参数是C风格还是C++风格字符串（std::string）进行重载*/

void print(const char* str)
{
    std::cout << "C-String : " << str << std::endl;
}

void print(const std::string& str)
{
    std::cout << "Cpp-String : " << str << std::endl;
}

int main()
{
    print("Hello world");
    print(std::string("Hello world"));

    return 0;
}