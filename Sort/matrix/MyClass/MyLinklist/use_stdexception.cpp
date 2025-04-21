#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class MyStack{
public:
    struct Node{
        T val;;;];n
        Node* next;
        Node(T v = 0, Node* p = nullptr) : val(v), next(p){}
    };
    MyStack() : top(nullptr){}
    ~MyStack(){ delete[] top;}
    T top();
    void pop();
    void push(T v);
    bool empty();
private:
    Node* to;
};
template<typename T>
T MyStack<T>::top(){
    if(empty()) throw logic_error("MyStack is empty!");
    else return to->val;
}
template<typename T>
void MyStack<T>::pop(){
    if(empty()) throw logic_error("MyStack is empty!");
    else{
        Node* temp = new(0, to);
        to  = to->next;
        delete temp;
    }
}
template<typename T>
void MyStack<T>::push(T v){
    try{
        Node* newnode = new(v, top);
        to = newnode;
    }catch (bad_alloc){
        throw;
    }
}
template<typename T>
bool MyStack<T>::empty(){
    return to == nullptr;
}
int main(){

    return 0;
}