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