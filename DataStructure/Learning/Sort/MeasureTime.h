#include <iostream>
#include <chrono>
#include <functional>

class Timer {
public:
    // 用于测量运行时间的静态方法
    template <typename Func, typename... Args>
    static void measureTime(const std::string& functionName, Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now(); // 开始时间
        func(std::forward<Args>(args)...); // 调用函数
        auto end = std::chrono::high_resolution_clock::now(); // 结束时间

        // 计算持续时间
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Function \"" << functionName << "\" took " 
                  << duration.count() << " milliseconds.\n";
    }
};

/*
这段代码是一个用于测量函数运行时间的类 Timer，它使用了几种 C++ 的语法和特性。以下是对主要语法的详细解释：

    1. 头文件引入
    #include <iostream>: 引入输入输出流库，用于 std::cout 打印输出。
    #include <chrono>: 引入时间库，提供高精度计时功能。
    #include <functional>: 引入函数对象和绑定功能，尽管在这个例子中并未直接使用。

    2. 类定义
    class Timer: 定义一个名为 Timer 的类。
    public: 访问修饰符，表示后面的成员是公共的，可以在类的外部访问。

    3. 模板函数
    template <typename Func, typename... Args>
    定义一个模板函数，允许函数接受任意类型的函数和参数。
    typename Func: 表示一个类型（即传入的函数类型）
    typename... Args: 这表示 Args 是一个参数包，可以接受零个或多个参数；
    ... 是关键字，表示后面可以跟任意数量的类型

    4. 静态方法
    static void measureTime(const std::string& functionName, Func func, Args&&... args)
    static: 表示该方法是静态的，可以通过类名直接调用，而不需要实例化对象。

    5. 时间测量
    auto start = std::chrono::high_resolution_clock::now();
    auto: 自动类型推断，start 会被推断为时间点类型。
    std::chrono::high_resolution_clock::now(): 获取当前高精度时间点。

    6. 函数调用
    func(std::forward<Args>(args)...);
    func(...): 调用传入的函数 func，并使用 std::forward 转发参数，以保留参数的值类别（左值或右值）
    std::forward<Args>(args)...: 将参数包展开并转发，保证函数在调用时能保持参数的特性（如引用、值）
    args: 是传递给函数的实际参数，它们会被存储在参数包中
    ...: 展开参数包，将其传递给 func 函数
    std::forward<Args>: 保持参数的值类别（左值或右值），确保

    7. 计算持续时间
    auto end: 获取结束时间点。
    std::chrono::duration<double, std::milli>: 创建一个持续时间对象，表示时间间隔，单位为毫秒。

    8. 输出结果
    std::cout: 输出流，用于打印信息。
    duration.count(): 获取持续时间的数值。

    9.示例
    Timer::measureTime("exampleFunction", exampleFunction, arg1, arg2);
    exampleFunction: 是一个函数指针。
    arg1 和 arg2: 是要传递给 exampleFunction 的参数。Args 包含 arg1 和 arg2

    总结
    这段代码使用了 C++ 的类、模板、静态方法、时间测量、函数调用、参数转发等特性，构建了一个通用的计时器，可以用于测量任何函数的运行时间。
*/