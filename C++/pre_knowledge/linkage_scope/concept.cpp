/*无链接（No Linkage）: 局部变量没有链接，因为它们只在定义它们的代码块内部可见。

内部链接（Internal Linkage）: 使用 static 关键字限定的全局变量或函数仅在定义它们的文件内部可见。

外部链接（External Linkage）: 没有 static 限定的全局变量和函数是可见的并且可以在其他文件中通过 extern 关键字访问。

下面是一个展示内部链接和外部链接的示例：

file1.cpp:

#include <iostream>

static int internalLinkageVar = 10; // 内部链接变量
int externalLinkageVar = 20; // 外部链接变量

static void internalFunction() { // 内部链接函数
    std::cout << "Internal function in file1" << std::endl;
}

void externalFunction() { // 外部链接函数
    std::cout << "External function in file1" << std::endl;
}


file2.cpp:

#include <iostream>

// 尝试访问file1.cpp中的变量和函数
extern int externalLinkageVar; // 正确：可以访问外部链接变量
// extern int internalLinkageVar; // 错误：内部链接变量在这里不可见

extern void externalFunction(); // 正确：可以访问外部链接函数
// extern void internalFunction(); // 错误：内部链接函数在这里不可见

int main() {
    std::cout << "External variable: " << externalLinkageVar << std::endl;
    externalFunction();
    return 0;
}
在file2.cpp中，我们可以通过extern关键字来声明并访问file1.cpp中的外部链接变量和函数。但是内部链接的变量和函数对file2.cpp来说是不可见的。

总结
局部作用域的变量仅在定义它们的代码块中可见。
全局作用域的变量在其整个文件中都可见。
内部链接的名字只能在定义它们的文件中使用。
外部链接的名字可以跨文件使用，但需要使用extern关键字进行声明。
