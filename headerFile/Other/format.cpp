C++20 引入了 std::format 函数，这是一个强大的格式化工具，类似于 Python 中的 f-string 和 str.format
std::format 可以用来格式化字符串,并且支持多种数据类型和格式化选项

1. std::format 函数
std::format 函数用于格式化字符串,它的基本用法是将格式字符串和一个或多个参数传递给 std::format,然后返回一个格式化后的字符串

基本语法
#include <format>
std::string formatted_string = std::format("format string", args...);

示例
#include <format>
#include <iostream>

int main() {
    int year = 2024;
    std::string name = "GPT-4o";
    
    std::string result = std::format("Hello, {}! The year is {}.", name, year);
    std::cout << result << std::endl; // 输出: Hello, GPT-4o! The year is 2024.
    
    return 0;
}
2. 格式字符串语法
格式字符串的语法与 Python 的格式化字符串类似。格式说明符位于大括号 {} 内，可以包含以下部分：

位置参数: {} 或 {index}
格式说明符: {:format_spec}
位置参数
std::string result = std::format("{1} {0}", "world", "Hello");
std::cout << result << std::endl; // 输出: Hello world

格式说明符
格式说明符可以包括对齐,填充,宽度,类型等信息

填充和对齐
<: 左对齐
>: 右对齐
^: 居中对齐
std::string result = std::format("{:<10}", "left");
std::cout << result << std::endl; // 输出: left  

宽度
std::string result = std::format("{:5}", 42);
std::cout << result << std::endl; // 输出: "   42"

类型
d: 十进制整数
x: 十六进制整数
f: 浮点数
std::string result = std::format("{:0>4d}", 42);
std::cout << result << std::endl; // 输出: 0042

3. std::format_to 函数
std::format_to 函数用于将格式化后的字符串写入到指定的输出迭代器。
基本语法
#include <format>
#include <vector>
std::vector<char> buffer;
std::format_to(std::back_inserter(buffer), "Hello, {}!", "world");

4. std::formatted_size 函数
std::formatted_size 函数返回格式化字符串的长度，而不实际生成该字符串。
基本语法
#include <format>

std::size_t size = std::formatted_size("Hello, {}!", "world");

5. std::vformat 函数
std::vformat 用于处理 format 参数包的变体。
基本语法
#include <format>
#include <vector>
#include <stdarg.h> // for va_list
std::string vformat(const std::string& format_str, std::va_list args) {
    return std::vformat(format_str, args);
}

总结
C++20 的 <format> 库提供了强大的字符串格式化功能，类似于 Python 的格式化机制。
std::format 是最常用的函数，通过简单的语法可以实现复杂的格式化需求。
其他函数如 std::format_to、std::formatted_size 和 std::vformat 则提供了更多的灵活性和功能。

