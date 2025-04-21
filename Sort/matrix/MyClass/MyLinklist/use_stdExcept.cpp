#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
//用的异常规范
template<typename T>
class Stack{
public:
    Stack() : top(nullptr){}
    ~Stack(){delete top;}
    bool isEmpty() const;
    void push(T val) throw(bad_alloc);
    T getTop() const throw(logic_error);
    void pop() throw(logic_error);
private:
    struct Node{
        T val;
        Node* next;
        Node(T val = 0, Node* p = nullptr) : val(val), next(p){}
    };
    Node* top;
};
template<typename T>
void Stack<T>::push(T val) throw(bad_alloc){
    try{
        Node* newNode = new Node(val, top);
        top = newNode;
    }catch(bad_alloc){
        throw;
    }
}
template<typename T>
bool Stack<T>::isEmpty() const {return top == nullptr;}

template<typename T>
T Stack<T>::getTop() const throw(logic_error){
    if(top == nullptr) throw logic_error("getTop from empty stack");
    else return top->val;
}

template<typename T>
void Stack<T>::pop() throw(logic_error){
    if(top == nullptr) throw logic_error("pop from empty stack!");
    else{
        Node* temp = new Node;
        temp = top;
        top = top->next;
        delete temp;
    }
}
int main(){
    Stack<int> stack;
    double a = 6.07;
    //string s = "hhhhhh";
    stack.push(a);
    //stack.push(s);
    while (!stack.isEmpty()) {cout << stack.getTop() << " "; stack.pop();}
    //cout << stack.getTop() << endl;
    return 0;
}