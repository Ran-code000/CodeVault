iomanip 中定义的常用的操作符：

std::setprecision: 设置浮点数的精度。

std::setw: 设置下一个数据的最小宽度。

std::setfill: 设置用于填充宽度剩余部分的字符。

std::setiosflags: 设置格式化标志，如 std::ios::left 或 std::ios::right。

std::resetiosflags: 清除格式化标志。

std::setbase: 设置数字的基数(例如,10表示十进制,16表示十六进制)

iomanip 中的操作符通常会影响紧随其后的输出操作，直到对应的格式标志被重置。
这些操作符可与输入输出流(如 std::cout, std::cin, std::ofstream, std::ifstream等)一起使用

std::endl除了输出换行符外,还会刷新输出缓冲区,这可能在不需要立即刷新时导致不必要的性能开销。
如果只是为了换行，使用\n通常更好 