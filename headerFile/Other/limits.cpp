<limits> 是 C++ 标准库的一个头文件，它包含了一系列模板类和函数，用于获取关于算术类型的属性，
比如最大值、最小值、位数等。这些信息对于编写可移植和高效的程序非常重要，尤其是涉及到模板元编程时。
核心的模板类是 std::numeric_limits<T>，其中 T 是一个算术类型，比如 int、float、double 等。

以下是 std::numeric_limits 类的成员函数和静态成员变量，以及它们的用法：

static constexpr bool is_specialized - 指示是否为特定类型提供了特化。
static constexpr T min() - 返回类型 T 的最小可能值。
static constexpr T max() - 返回类型 T 的最大可能值。
static constexpr T lowest() - 返回类型 T 可以表示的最低值。
static constexpr int digits - 返回类型 T 的基数为10时的位数。
static constexpr int digits10 - 以10为基数时类型 T 可以无损失表示的最大十进制位数。
static constexpr bool is_signed - 指示类型 T 是否为有符号类型。
static constexpr bool is_integer - 指示类型 T 是否为整数类型。
static constexpr bool is_exact - 指示类型 T 的表示是否为精确的。
static constexpr int radix - 返回类型 T 的基数。
static constexpr T epsilon() - 返回类型 T 的机器精度。
static constexpr T round_error() - 返回最大舍入误差。
static constexpr int min_exponent - 对浮点数类型，返回最小的可能的指数值。
static constexpr int min_exponent10 - 对浮点数类型,返回最小的可能的以10为基数的指数值。
static constexpr int max_exponent - 对浮点数类型，返回最大的可能的指数值。
static constexpr int max_exponent10 - 对浮点数类型,返回最大的可能的以10为基数的指数值。
static constexpr bool has_infinity - 指示类型 T 是否支持无穷大值。
static constexpr bool has_quiet_NaN - 指示类型 T 是否支持安静的 NaN(非数字)值。
static constexpr bool has_signaling_NaN - 指示类型 T 是否支持发信号的 NaN 值。
static constexpr float_denorm_style has_denorm - 指示类型 T 是否支持非正规化数。
static constexpr bool has_denorm_loss - 指示类型 T 在算术运算中是否可能损失非正规化数。
static constexpr T infinity() - 返回类型 T 的无穷大表示。
static constexpr T quiet_NaN() - 返回类型 T 的安静 NaN 值。
static constexpr T signaling_NaN() - 返回类型 T 的发信号 NaN 值。
static constexpr T denorm_min() - 返回类型 T 的最小正非正规化数。
static constexpr bool is_iec559 - 指示类型 T 是否符合 IEC $559/IEEE $754 标准。
static constexpr bool is_bounded - 指示类型 T 的值是否有界。
static constexpr bool is_modulo - 对于整数类型，指示 T 是否在算术溢出时环绕。
*/