#include <iostream>
#include <stdexpect>
using namespace std;
template<typename T>
class Stack{
public:
    Stack() : top(nullptr){}
    ~Stack(){}
    void push(T val);
    void pop();
    T top() const;
    bool empty() const;
private:
    struct Node{
        T val;
        Node* next;
        Node(T val, Node* p = nullptr) : val(val), next(p){}
    };
    Node* top;
};
template<typename T>
void Stack<T>::push(T val){ Node* newnode = new Node(val, top); top = newnode;}
template<typename T>
void Stack<T>::pop(){
    if(empty()) throw out_of_range("Stack is empty");
    else{
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}
template<typename T>
T Stack<T>::top() const{ return top->val;}
template<typename T>
bool Stack<T>::empty() const{ return top == nullptr;}
int main(){
    Stack<int> stack; // 实例化一个保存int型元素的栈
    for (int i = 1; i < 9; i++) stack.push(i);
    while (!stack.empty()){cout << stack.top() << " "; stack.pop();}
    return 0;
}
