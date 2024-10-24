<stdexcept> 是一个C++标准库头文件，它定义了一系列标准异常类，它们都继承自 exception 基类
这些异常类用于报告标准库函数在执行过程中遇到的错误情况<stdexcept> 中主要包含的异常类有：

1.logic_error - 逻辑错误，程序应该能够避免的错误

invalid_argument - 当一个无效的参数被传递给一个函数时抛出
domain_error - 当一个数学函数接收到一个有效但不适用的参数时抛出
length_error - 当创建了一个太大的 string 或者其他对象时抛出
out_of_range - 当访问一个序列之外的元素时抛出，例如 vector 或 array


2.runtime_error - 运行时错误, 通常由外部因素引起, 程序难以预防

range_error - 当结果值超出了预期的范围时抛出
overflow_error - 当发生算术上溢时抛出
underflow_error - 当发生算术下溢时抛出

这些异常类通常在函数内部使用 throw 关键字抛出，并在函数外部用 try 和 catch 块进行捕获处理

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        // invalid_argument
        void processInput(int value) {
            if (value < 0) {
                throw invalid_argument("Negative value not allowed");
            }
            // 处理输入...
        }
        processInput(-1); // 这将抛出一个 invalid_argument 异常
        // out_of_range
        vector<int> vec{1, 2, 3};
        cout << vec.at(3); // 这将抛出一个 out_of_range 异常
        // length_error
        string str;
        str.reserve(static_cast<size_t>(-1)); // 这将抛出一个 length_error 异常
        // range_error, overflow_error, underflow_error 通常用于数学计算错误
        // 但是 overflow_error 和 underflow_error 在标准数学库中不会抛出
        // 需要用户在自己的代码中进行判断并抛出
        // 例如:
        double compute(double value) {
            double result = value * 1000.0;
            if (result > numeric_limits<double>::max()) {
                throw overflow_error("Overflow in compute()");
            }
            return result;
        }
        compute(numeric_limits<double>::max()); // 这可能抛出一个 overflow_error 异常
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
    }
    catch (const length_error& e) {
        cerr << "Length error: " << e.what() << endl;
    }
    catch (const range_error& e) {
        cerr << "Range error: " << e.what() << endl;
    }
    catch (const overflow_error& e) {
        cerr << "Overflow error: " << e.what() << endl;
    }
    catch (const underflow_error& e) {
        cerr << "Underflow error: " << e.what() << endl;
    }
    catch (const exception& e) {
        // 这个捕获块可以捕获所有派生自 exception 的异常
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
