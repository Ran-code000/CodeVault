#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
template<typename T>                                                                                                                                                                                                                                                               
class MyStack {
private:
    vector<T> container;  // 使用vector作为底层容器
public:
    MyStack() = default;
    bool empty() const { return container.empty();}
    size_t size() const { return container.size();}                                                                                                                    
    T& top() {
        if (empty()) throw out_of_range("Stack is empty");
        return container.back();
    }
    const T& top() const {
        if (empty()) throw out_of_range("Stack is empty");
        return container.back();
    }
    void push(const T& value) { container.push_back(value);}
    void pop() {
        if (empty()) throw out_of_range("Stack is empty");
        container.pop_back();
    }
};

