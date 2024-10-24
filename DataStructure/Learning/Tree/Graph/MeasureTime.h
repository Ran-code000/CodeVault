#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <utility>
using namespace std;

// 模板函数，用于测量函数的运行时间
// C++模板的通用函数模板，用于测量任何函数的执行时间。
// 它结合了模板参数包、完美转发以及C++的标准库功能来完成
//typename... Args：表示一个模板参数包，用于接受不确定数量的参数，这些参数将传递给被测量的函数
template<typename Func, typename... Args>
//这个参数 func 是你想测量的函数，它可以是普通函数、成员函数或lambda等不同的可调用对象
//Args&&... args：这个部分表示传递给函数的参数包，通过 && 实现了万能引用，从而支持传递左值、右值参数
void measureTime(const string& functionName, Func func, Args&&... args){
    //high_resolution_clock 是 C++ 标准库中的一种时钟，能够提供尽可能高精度的时间信息
    auto start = chrono::high_resolution_clock::now();  
    //forward<Args>(args)...：通过 std::forward 进行完美转发。
    //这使得参数包中的每个参数都能保持其原本的左值或右值属性，以确保函数能够正确处理传递的参数，无论它们是临时变量、常量还是引用
    func(forward<Args>(args)...);                       
    auto end = chrono::high_resolution_clock::now();    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << functionName << " running time: " << duration << "μs" << endl;
}
#endif // MYGRAPH_H