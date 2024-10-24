#include <iostream>
#include <string>
#include <stdexcept>
#include <any>
using namespace std;
class Stack{
public:
    Stack() : top(nullptr){}
    ~Stack(){delete top;}
    bool isEmpty() const;
    template<typename T>
    void push(T val) throw(bad_alloc);
    template<typename T>
    T getTop() const throw(logic_error);
    void pop() throw(logic_error);
private:
    struct Node{
        std::any val;
        Node* next;
        Node(std::any val = 0, Node* p = nullptr) : val(val), next(p){}
    };
    Node* top;
};
template<typename T>
void Stack::push(T val) throw(bad_alloc){
    try{
        Node* newNode = new Node(val, top);
        top = newNode;
    }catch(bad_alloc){
        throw;
    }
}
bool Stack::isEmpty() const {return top == nullptr;}

template<typename T>
T Stack::getTop() const throw(logic_error){
    if(top == nullptr) throw logic_error("getTop from empty stack");
    else return std::any_cast<T>(top->val);
}

void Stack::pop() throw(logic_error){
    if(top == nullptr) throw logic_error("pop from empty stack!");
    else{
        Node* temp = new Node;
        temp = top;
        top = top->next;
        delete temp;
    }
}
int main(){
    Stack stack;
    double a = 6.07;
    string s = "hhhhhh";
    stack.push(a);
    //stack.push(s);
    //stack.getTop<std::any>().type().name() << ": " << std::any_cast<string>(stack.getTop<std::any>()) << endl;
    while (!stack.isEmpty()) {
        cout << stack.getTop<std::any>().type.name() << ":" << stack.getTop<std::any>() << endl;
    }
    return 0;
}