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
int main(){
    MyStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "{10, 20, 30}" << endl;
    cout << "Top element: " << stack.top() << endl;
    stack.pop();
    cout << "Top element after pop: " << stack.top() << endl;
    cout << "Stack size: " << stack.size() << endl;
    stack.pop();
    stack.pop();
    cout << "After twice pop......" << endl;
    cout << "Stack empty: " << boolalpha << stack.empty() << endl;
    return 0;
}
