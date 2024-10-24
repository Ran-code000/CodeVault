#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    std::string str;
    std::cin >> str;

    std::string s = "VK";
    std::string v = "VV";
    std::string k = "KK";

    int cnt = 0;
    int pos = str.find(s);

    while( pos != std::string::npos)
    {
        cnt++;
        str[pos] = 'X';
        str[pos+1] = 'X';
        pos = str.find(s,pos+s.size());
        
    }

    
    if((str.find(v) != std::string::npos || str.find(k) != std::string::npos))
    //不能写 str.find(v) || str.find(k)
    //std::string::find函数如果找不到子字符串，则会返回std::string::npos，这是一个特殊的常量，通常等于-1，
    //但是以无符号整数的形式表示。
    //即使 str.find(v)或 str.find(k) 未找到匹配项，它们的返回值（std::string::npos）在逻辑表达式中仍被认为是true，
    //因为任何非零值在逻辑表达式中都被视为true。
    {
        cnt++;
    }

    std::cout << cnt << std::endl;

    return 0;                                                     
}

/*
std::string::npos 与 EOF 的区别

std::string::npos 是 std::string 类中定义的一个常量，表示一个非法的位置，
其值为最大的可能的 size_t 值，通常用于字符串搜索操作中表示没有找到匹配项。

EOF 是一个宏，定义在 <cstdio> 或 <stdio.h> 中，表示文件结束（End Of File）。
在从文件或标准输入读取时，如果达到了输入流的末尾，函数如 fgetc 或 std::cin.get() 将返回 EOF。


这两者在使用上有本质的区别，std::string::npos 用于字符串操作，而 EOF 用于文件或标准输入流的操作。

1.使用 std::string::npos

#include <iostream>
#include <string>

int main() 
{
    std::string s = "Hello, world!";
    size_t pos = s.find("world");
    if (pos != std::string::npos) 
    {
        std::cout << "'world' found at position: " << pos << std::endl;
    } else 
    {
        std::cout << "'world' not found." << std::endl;
    }
    return 0;
}

2。处理 EOF

#include <iostream>

int main() 
{
    std::cout << "Enter characters, EOF (Ctrl+D or Ctrl+Z) to end:\n";
    int ch;

    while ((ch = std::cin.get()) != EOF) 
    { // 读取字符直到EOF
        std::cout.put(char(ch));
    }
    std::cout << "\nEOF encountered." << std::endl;

    return 0;
}

在第一个例子中，我们使用 std::string::npos 来判断字符串 “world” 是否在 s 中找到。
在第二个例子中，通过判断 std::cin.get() 的返回值是否为 EOF 来检测输入流是否结束。
*/