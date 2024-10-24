#include <iostream>

void overloaded(int &arg) {
    std::cout << "by lvalue\n";
}

void overloaded(int &&arg) {
    std::cout << "by rvalue\n";
}

template <typename T>
void forward(T&& arg) {
    overloaded(std::forward<T>(arg)); // 根据arg的类型，转发给相应的函数
}

int main() {
    int x = 5;
    
    std::cout << "Calling forward with lvalue:\n";
    forward(x); // x是一个lvalue，因此调用overloaded(int &arg)
    
    std::cout << "Calling forward with rvalue:\n";
    forward(5); // 5是一个rvalue，因此调用overloaded(int &&arg)
    
    return 0;
}
/*
overloaded 函数被重载了两次：
一次接受一个左值引用（int &arg），另一次接受一个右值引用（int &&arg）。
通过模板函数forward，我们可以根据传入的参数类型（左值还是右值）转发给相应的重载函数。
这展示了右值引用在优化代码和资源管理中的用途，尤其是在实现移动构造函数和移动赋值操作符时。
*/