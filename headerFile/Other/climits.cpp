<climits> 是一个 C++ 标准库头文件，它包含了一系列宏定义，这些宏定义了各种整数类型的限制。
这些限制包括类型可以表示的最大值、最小值和位数。<climits> 实际上是 C 语言头文件 <limits.h> 的 C++ 版本。

下面是 <climits> 中定义的宏：

CHAR_BIT:定义了一个字节中的位数,通常是8。
CHAR_MAX:定义了类型 char 的最大值。
CHAR_MIN:定义了类型 char 的最小值。
INT_MAX:定义了类型 int 的最大值。
INT_MIN:定义了类型 int 的最小值。
LONG_MAX:定义了类型 long 的最大值。
LONG_MIN:定义了类型 long 的最小值。
SCHAR_MAX:定义了类型 signed char 的最大值。
SCHAR_MIN:定义了类型 signed char 的最小值。
SHRT_MAX:定义了类型 short 的最大值。
SHRT_MIN:定义了类型 short 的最小值。
UCHAR_MAX:定义了类型 unsigned char 的最大值,signed char 和 unsigned char 的范围不同。
UINT_MAX:定义了类型 unsigned int 的最大值。
ULONG_MAX:定义了类型 unsigned long 的最大值。
USHRT_MAX:定义了类型 unsigned short 的最大值。
LLONG_MAX:定义了类型 long long 的最大值(C++11及以后版本)。
LLONG_MIN:定义了类型 long long 的最小值(C++11及以后版本)。
ULLONG_MAX:定义了类型 unsigned long long 的最大值(C++11及以后版本)。


下面是如何使用 <climits> 中定义的宏的示例代码：

#include <climits>
#include <iostream>

int main() {
    std::cout << "The number of bits in a byte CHAR_BIT is: " << CHAR_BIT << std::endl;
    std::cout << "The maximum value of CHAR_MAX is: " << CHAR_MAX << std::endl;
    std::cout << "The minimum value of CHAR_MIN is: " << static_cast<int>(CHAR_MIN) << std::endl;
    std::cout << "The maximum value of INT_MAX is: " << INT_MAX << std::endl;
    std::cout << "The minimum value of INT_MIN is: " << INT_MIN << std::endl;
    // ... 以此类推，列出所有其他的限制

    // 特别注意无符号类型的最小值通常是0，因此没有定义最小值的宏
    std::cout << "The maximum value of UCHAR_MAX is: " << static_cast<unsigned>(UCHAR_MAX) << std::endl;

    // C++11及以后版本的 long long 类型
    std::cout << "The maximum value of LLONG_MAX is: " << LLONG_MAX << std::endl;
    std::cout << "The minimum value of LLONG_MIN is: " << LLONG_MIN << std::endl;
    std::cout << "The maximum value of ULLONG_MAX is: " << ULLONG_MAX << std::endl;

    return 0;
}
在本例中，我们使用 <climits> 提供的宏来打印出不同整数类型的最大值和最小值。

注意,当打印无符号类型的最小值时(其实它总是0),我们没有使用宏,而是直接写出了0。
对于 char 类型的最小值，我们使用了 static_cast<int>() 来确保以整数形式打印出来，因为 char 类型可能被解释为可打印的字符。
在 C++ 中,char 类型实际上是一个小的整数类型,它通常用来存储字符数据。根据平台和编译器的设置,char 可以是有符号的(signed)
或无符号的(unsigned)，这意味着它可以表示的值的范围有所不同。

如果 char 是有符号的，它通常可以表示 -128 到 127 的整数值。
如果 char 是无符号的，它可以表示 0 到 255 的整数值。
当你尝试打印一个 char 值时,C++ 默认会将其作为字符来处理。例如：

char c = 65; // ASCII 码中，65 对应 'A'
std::cout << c; // 这会打印字符 'A'
当想要打印出 char 类型的数值而不是字符时，需要将 char 转换为一个整数类型。可以使用 static_cast<int>() 来实现：

char c = 65;
std::cout << static_cast<int>(c); // 这会打印整数 65 而不是字符 'A'
如果 c 是有符号 char 的最小值(例如，-128),直接打印 c 可能会尝试打印一个不可打印的字符，
因为标准 ASCII 表中并没有对应 -128 到 -1 的字符。因此，为了看到实际的整数值，你需要将 char 转换为 int

char min_char = std::numeric_limits<char>::min(); // 假设 char 是有符号的，这可能是 -128
std::cout << static_cast<int>(min_char); // 会打印 -128
使用 static_cast<int>() 可以确保无论 char 是否有符号，其值都会以整数形式打印出来，而不是尝试显示对应的字符，
这可能会导致混淆或者不可打印的输出。

请记住，这些宏定义的确切值取决于你所使用的系统和编译器实现。
例如,INT_MAX 在大多数平台上是 2147483647,但这不是所有平台的标准
