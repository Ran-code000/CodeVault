<cstdint> 头文件是 $C++11 $标准库的一部分，它提供了一组固定宽度的整数类型。这些类型是跨平台的，它们的大小不会因编译器或操作系统而改变，这对于需要确保整数大小一致性的程序很有用，例如在进行硬件编程或网络通信时。

下面是 <cstdint> 中定义的类型列表和它们的使用例子：

固定宽度整数类型：
int8_t: 确保有8位的有符号整数类型。
uint8_t: 确保有8位的无符号整数类型。
int16_t: 确保有16位的有符号整数类型。
uint16_t: 确保有16位的无符号整数类型。
int32_t: 确保有32位的有符号整数类型。
uint32_t: 确保有32位的无符号整数类型。
int64_t: 确保有64位的有符号整数类型。
uint64_t: 确保有64位的无符号整数类型。
最小宽度整数类型：
int_least8_t: 至少8位的有符号整数。
uint_least8_t: 至少8位的无符号整数。
int_least16_t: 至少16位的有符号整数。
uint_least16_t: 至少16位的无符号整数。
int_least32_t: 至少32位的有符号整数。
uint_least32_t: 至少32位的无符号整数。
int_least64_t: 至少64位的有符号整数。
uint_least64_t: 至少64位的无符号整数。
快速最小宽度整数类型：
int_fast8_t: 在当前平台上最快的至少8位有符号整数。
uint_fast8_t: 在当前平台上最快的至少8位无符号整数。
int_fast16_t: 在当前平台上最快的至少16位有符号整数。
uint_fast16_t: 在当前平台上最快的至少16位无符号整数。
int_fast32_t: 在当前平台上最快的至少32位有符号整数。
uint_fast32_t: 在当前平台上最快的至少32位无符号整数。
int_fast64_t: 在当前平台上最快的至少64位有符号整数。
uint_fast64_t: 在当前平台上最快的至少64位无符号整数。
整数类型宽度指定符：
INTn_C(value): n 代表位数，用于定义 int_leastn_t 类型的常量。
UINTn_C(value): n 代表位数，用于定义 uint_leastn_t 类型的常量。
最大宽度整数类型：
intmax_t: 可以表示的值最大的整数类型。
uintmax_t: 可以表示的值最大的无符号整数类型。
宏：
INTn_MIN, INTn_MAX, UINTn_MAX: 定义了对应类型的最小值和最大值。
INT_LEASTn_MIN, INT_LEASTn_MAX, UINT_LEASTn_MAX: 至少 n 位宽的类型的最小值和最大值。
INT_FASTn_MIN, INT_FASTn_MAX, UINT_FASTn_MAX: 最快的至少 n 位宽的类型的最小值和最大值。
INTMAX_MIN, INTMAX_MAX, UINTMAX_MAX: 最大宽度整数类型的最小值和最大值。
PTRDIFF_MIN, PTRDIFF_MAX: 指针差类型的最小值和最大值。
SIG_ATOMIC_MIN, SIG_ATOMIC_MAX: 信号原子类型的最小值和最大值。
SIZE_MAX: size_t 类型的最大值。
WCHAR_MIN, WCHAR_MAX: 宽字符类型的最小值和最大值。
WINT_MIN, WINT_MAX: 宽整数类型的最小值和最大值。
$C++ $代码示例：
cpp
复制
#include <cstdint>
#include <iostream>

int main() {
    // 固定宽度整数类型
    int8_t myInt8 = 127; // 8-bit signed integer
    uint8_t myUInt8 = 255; // 8-bit unsigned integer

    // 最小宽度整数类型
    int_least16_t myIntLeast16 = 32767; // At least 16-bit signed integer
    uint_least16_t myUIntLeast16 = 65535; // At least 16-bit unsigned integer

    // 快速最小宽度整数类型
    int_fast32_t myIntFast32 = 2147483647; // Fast at least 32-bit signed integer
    uint_fast32_t myUIntFast32 = 4294967295U; // Fast at least 32-bit unsigned integer

    // 最大宽度整数类型
    intmax_t myIntMax = INTMAX_MAX; // Maximum width signed integer
    uintmax_t myUIntMax = UINTMAX_MAX; // Maximum width unsigned integer

    std::cout << "int8_t: " << static_cast<int>(myInt8) << std::endl;
    std::cout << "uint8_t: " << static_cast<unsigned int>(myUInt8) << std::endl;
    std::cout << "int_least16_t: " << myIntLeast16 << std::endl;
    std::cout << "uint_least16_t: " << myUIntLeast16 << std::endl;
    std::cout << "int_fast32_t: " << myIntFast32 << std::endl;
    std::cout << "uint_fast32_t: " << myUIntFast32 << std::endl;
    std::cout << "intmax_t: " << myIntMax << std::endl;
    std::cout << "uintmax_t: " << myUIntMax << std::endl;

    return 0;
}
在实际编程中，这些类型应该根据您的应用程序中对整数大小和性能的具体要求来选择。

