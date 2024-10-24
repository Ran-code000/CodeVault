/*预处理指令包括宏定义（#define），条件编译（如#ifdef, #ifndef, #if, #endif），包含其他文件（#include），
以及其它如#pragma等。

以下是预处理器的一些基本使用方法的例子：

1.宏定义和宏函数

// 宏定义可以定义常量
#define PI 3.14159

// 宏也可以定义带有参数的宏函数
#define SQUARE(x) ((x)*(x))

#include <iostream>

int main() {
    std::cout << "The value of PI is: " << PI << std::endl;
    std::cout << "The square of 5 is: " << SQUARE(5) << std::endl;

    return 0;
}
2.条件编译

// 使用条件编译可以根据不同的条件编译不同的代码块
#define DEBUG

#include <iostream>

int main() {
#ifdef DEBUG
    std::cout << "Debug mode is on." << std::endl;
#else
    std::cout << "Debug mode is off." << std::endl;
#endif

    return 0;
}
3.包含其他文件

// #include 指令用于包含其他文件的内容
#include <iostream> // 包含标准库头文件
#include "myheader.h" // 包含用户自定义的头文件

int main() {
    // 使用iostream和myheader.h中定义的内容
}
myheader.h 可以是用户自己定义的头文件，其内容可能如下：


// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

void myFunction() {
    // 函数的实现
}

#endif // MYHEADER_H

4.pragma指令

// #pragma 指令用于提供额外的编译器指令
#pragma once // 保证头文件内容只被包含一次

#include <iostream>

int main() {
    // 使用编译器特定的指令
}
#pragma once 是一个常见的非标准但广泛支持的指令，用于防止同一个文件被包含（include）多次。

