<cassert> 是一个 C++ 标准库头文件，它提供了一个宏 assert,用于辅助调试程序。assert 宏是一个诊断工具，
它允许程序员检查特定的假设，并在假设为假时终止程序。当 assert 宏中的表达式为 false(即为 0)时,
assert 将写入一条错误消息到标准错误流 stderr 并通过调用 abort 函数来终止程序。

assert 宏是用于验证程序中的不变量和前后条件的，它在运行时评估这些条件。如果条件失败，
assert 将提供关于失败位置的信息和失败的条件表达式。

用法很简单:assert(expression);

如果 expression 为真（非零），则 assert 宏不做任何事情，程序继续执行。如果 expression 为假（零），则 assert 宏会打印一条错误消息并终止程序。

默认情况下,assert 宏是启用的。但是，如果在包含 <cassert> 之前定义了宏 NDEBUG,则 assert 宏不会执行任何操作，
它将被定义为空白（即不检查表达式）。

下面是 <cassert> 的一些基本用法示例：

#include <cassert>

int main() {
    int a = 10;
    int b = 0;

    // 正常的情况，不会有任何输出
    assert(a == 10);

    // 一个失败的断言，会终止程序，并提供错误信息
    // 这行代码会打印类似 "Assertion failed: b != 0, file example.cpp, line 10" 的信息
    assert(b != 0);

    // 如果 NDEBUG 定义了，下面的 assert 将不会执行任何检查
    #define NDEBUG
    #include <cassert>

    // 这个断言即使条件失败也不会有任何效果
    assert(a == 0);

    return 0;
}
在实际的程序中，你应该将 assert 用于检查那些"绝对不可能发生但又偶尔会发生"的情况。在发布版本的代码中，通常会定义 NDEBUG 宏以禁用 assert，避免对性能的影响和向用户暴露调试细节。

要注意的是 <cassert> 只包含 assert 宏的定义，没有其他的内容。这使得 <cassert> 是一个相对简单直接的头文件。

