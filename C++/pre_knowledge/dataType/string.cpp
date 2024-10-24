# include <iostream>
# include <string>

int main()
{
    std::string str;
    std::cout << "请随便输入一个字符串 : " ;
    std::getline(std::cin , str);
    std::cout << "您输入的字符串为 : " << str;
    return 0;
}

/*std::string 类：
size() 或 length(): 返回字符串的长度。
empty(): 检查字符串是否为空。
substr(): 获取字符串的一个子串。
append(), operator+=: 用于拼接字符串。
find(): 在字符串中查找子串或字符。
compare(): 比较两个字符串。*/