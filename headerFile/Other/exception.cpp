C++ 的<exception>头文件提供了一系列与异常处理相关的类和函数，这些工具帮助程序员处理和报告异常情况

1. exception
概述
用途:标准异常类,是所有标准C++异常类的基类

方法：
what(): 返回一个C风格字符串,描述异常的原因

示例
#include <iostream>
#include <exception>
int main() {
    try {
        throw exception();
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
    return 0;
}

2. bad_alloc
概述
用途:当new操作符无法分配内存时抛出
继承:继承自exception

示例
#include <iostream>
#include <exception>
#include <new> // for bad_alloc

int main() {
    try {
        int* p = new int[100000000000]; // 试图分配大量内存(new 分配的内存在堆上)
    } catch (const bad_alloc& e) {
        cerr << "Caught bad_alloc: " << e.what() << endl;
    }
    return 0;
}

3. bad_cast
概述
用途:当dynamic_cast无法进行安全的类型转换时抛出
继承:继承自exception

示例
#include <iostream>
#include <exception>
#include <typeinfo> // for bad_cast

class Base {
    virtual void foo() {}
};

class Derived : public Base {};

int main() {
    try {
        Base* b = new Base();
        Derived& d = dynamic_cast<Derived&>(*b); // 错误的类型转换
    } catch (const bad_cast& e) {
        cerr << "Caught bad_cast: " << e.what() << endl;
    }

    return 0;
}

4. bad_typeid
概述
用途:当对空指针使用typeid操作符时抛出
继承:继承自exception

示例
#include <iostream>
#include <exception>
#include <typeinfo> // for bad_typeid

class Base {
    virtual void foo() {}
};

int main() {
    try {
        Base* b = nullptr;
        cout << typeid(*b).name() << endl; // 对空指针使用typeid
    } catch (const bad_typeid& e) {
        cerr << "Caught bad_typeid: " << e.what() << endl;
    }

    return 0;
}

5. terminate
概述
用途：调用这个函数会立即终止程序
默认行为:调用abort(), 可以通过set_terminate设置自定义的行为

示例
#include <iostream>
#include <exception>

void customTerminate() {
    cerr << "Custom terminate function called!" << endl;
    abort();
}

int main() {
    set_terminate(customTerminate); // 设置自定义terminate函数
    terminate(); // 调用terminate
    return 0;
}

6. set_terminate
概述
用途:设置一个自定义的terminate处理函数

示例
#include <iostream>
#include <exception>

void customTerminate() {
    cerr << "Custom terminate handler called!" << endl;
    abort();
}
int main() {
    set_terminate(customTerminate); // 设置自定义的terminate处理函数
    terminate(); // 调用terminate

    return 0;
}

7. unexpected
概述
用途：当函数抛出一个未在其异常规范（已弃用）中声明的异常时调用

示例
#include <iostream>
#include <exception>
void customUnexpected() {
    cerr << "Custom unexpected handler called!" << endl;
    terminate();
}

void myFunction() throw(int) { // 异常规范（已弃用）
    throw 'a'; // 抛出未声明的异常
}

int main() {
    set_unexpected(customUnexpected); // 设置自定义的unexpected处理函数
    try {
        myFunction();
    } catch (...) {
        cerr << "Caught an exception" << endl;
    }

    return 0;
}

8. set_unexpected
概述
用途:设置一个自定义的unexpected处理函数

示例
#include <iostream>
#include <exception>

void customUnexpected() {
    cerr << "Custom unexpected handler called!" << endl;
    terminate();
}
void myFunction() throw(int) { // 异常规范（已弃用）
    throw 'a'; // 抛出未声明的异常
}
int main() {
    set_unexpected(customUnexpected); // 设置自定义的unexpected处理函数
    try {
        myFunction();
    } catch (...) {
        cerr << "Caught an exception" << endl;
    }

    return 0;
}

9. rethrow_exception
概述
用途：重新抛出捕获的异常
参数:一个exception_ptr对象

示例
#include <iostream>
#include <exception>
#include <stdexcept>

void handleException(exception_ptr eptr) {
    try {
        if (eptr) {
            rethrow_exception(eptr);
        }
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
}

int main() {
    exception_ptr eptr;
    try {
        throw runtime_error("Example exception");
    } catch (...) {
        eptr = current_exception();
    }

    handleException(eptr);

    return 0;
}

10. current_exception
概述
用途:捕获当前异常并返回exception_ptr对象

示例
#include <iostream>
#include <exception>
#include <stdexcept>

void handleException(exception_ptr eptr) {
    try {
        if (eptr) {
            rethrow_exception(eptr);
        }
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
}
int main() {
    exception_ptr eptr;
    try {
        throw runtime_error("Example exception");
    } catch (...) {
        eptr = current_exception();
    }

    handleException(eptr);

    return 0;
}

11. make_exception_ptr
概述
用途:创建一个exception_ptr对象, 指向给定的异常

示例
#include <iostream>
#include <exception>
#include <stdexcept>

void handleException(exception_ptr eptr) {
    try {
        if (eptr) {
            rethrow_exception(eptr);
        }
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
}
int main() {
    exception_ptr eptr = make_exception_ptr(runtime_error("Example exception"));

    handleException(eptr);

    return 0;
}

12. nested_exception
概述
用途：允许嵌套异常的抛出和捕获
典型用法：用于捕获异常并在捕获到的异常中嵌套另一个异常

示例
#include <iostream>
#include <exception>

void foo() {
    try {
        throw runtime_error("Error in foo");
    } catch (...) {
        throw_with_nested(runtime_error("Nested exception in foo"));
    }
}
void bar() {
    try {
        foo();
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
        try {
            rethrow_if_nested(e);
        } catch (const exception& nested) {
            cerr << "Nested exception: " << nested.what() << endl;
        }
    }
}
int main() {
    bar();
    return 0;
}

13. throw_with_nested
概述
用途：在当前捕获的异常中嵌套一个新的异常
throw_with_nested 用于在当前捕获的异常中嵌套一个新的异常.这可以帮助在处理异常时保留异常链，便于追踪异常的根源

用途
捕获和重新抛出: 在处理异常时, 可以捕获当前异常并用新的异常类型重新抛出, 同时保留原始异常的信息
多层次异常处理: 在复杂系统中, 异常可能会在多个层次上传播, 保留异常链可以帮助诊断和调试

示例
以下是一个使用throw_with_nested的示例:
#include <iostream>
#include <exception>
#include <stdexcept>

void functionA() {
    try {
        throw runtime_error("Error in functionA");
    } catch (...) {
        throw_with_nested(runtime_error("functionA failed"));
    }
}
void functionB() {
    try {
        functionA();
    } catch (...) {
        throw_with_nested(runtime_error("functionB failed"));
    }
}
void handleNestedException(const exception& e) {
    cerr << "Caught exception: " << e.what() << endl;
    try {
        rethrow_if_nested(e);
    } catch (const exception& nested) {
        handleNestedException(nested);
    } catch (...) {
        // No more nested exceptions
    }
}
int main() {
    try {
        functionB();
    } catch (const exception& e) {
        handleNestedException(e);
    }
    return 0;
}
解释
functionA:
抛出一个runtime_error异常
捕获所有异常, 并使用throw_with_nested嵌套一个新的runtime_error异常

functionB:
调用functionA, 并捕获所有异常
使用throw_with_nested嵌套一个新的runtime_error异常

handleNestedException:
捕获并打印当前异常信息
使用rethrow_if_nested尝试重新抛出嵌套的异常
递归处理所有嵌套的异常，直到没有更多嵌套异常

main:
调用functionB并捕获异常
使用handleNestedException处理捕获的异常

总结
通过使用throw_with_nested, 可以在捕获异常时保留原始异常, 便于调试和诊断复杂的异常处理情况, 
这个示例展示了如何捕获, 嵌套和处理多层次异常, 使得异常处理更加透明和易于维护

