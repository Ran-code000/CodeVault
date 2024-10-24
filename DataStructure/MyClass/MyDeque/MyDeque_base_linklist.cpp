#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class MyDeque {
private:
    struct Node{
        T val;
        Node* next;
        Node* prev;
        Node(const T& v) : val(v), next(nullptr), prev(nullptr){}
    };
    Node* head;
    Node* tail;
    size_t dqsize;
public:
    MyDeque() : head(nullptr), tail(nullptr), dqsize(0){}
    ~MyDeque(){while(!is_empty()) pop_front();}
    bool is_empty() const {return dqsize == 0;}
    size_t size() const {return dqsize;}
    T& front() {
        if (is_empty()) throw out_of_range("Deque is empty");
        return head->val;
    }
    const T& front() const {
        if (is_empty()) throw out_of_range("Deque is empty");
        return head->val;
    }
    T& back() {
        if (is_empty()) throw out_of_range("Deque is empty");
        return tail->val;
    }
    const T& back() const {
        if (is_empty()) throw out_of_range("Deque is empty");
        return tail->val;
    }
    void push_front(const T& v){
        Node* newnode = new Node(v);
        if(is_empty()) head = tail = newnode;
        else{
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        dqsize++;
    }
    void push_back(const T& v){
        Node* newnode = new Node(v);
        if(is_empty()) head = tail = newnode;
        else{
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        dqsize++;
    }
    void pop_front(){
        if(is_empty()) throw out_of_range("Deque is empty");
        else if(size() == 1) head = tail = nullptr, dqsize = 0;
        else{
            Node* temp = head;
            if(head) head = head->next;
            delete temp;
            if(head) head->prev = nullptr;//避免无限循环
        }
        dqsize--;
    }
    void pop_back(){
        if(is_empty()) throw out_of_range("deque is empty");
        else if(size() == 1) head = tail = nullptr, dqsize = 0;
        else{
            Node* temp = tail;
            if(tail) tail = tail->prev;
            delete temp;
            if(tail) tail->next = nullptr;//避免无限循环
        }
        dqsize--;
    }
};

int main(){
    MyDeque<int> dq;
    for(int i = 0; i < 7; i++) dq.push_back(i);
    cout << "{0, 1, 2, 3, 4, 5, 6}" << endl;
    cout << "Front element: " << dq.front() << endl;
    cout << "Back element: " << dq.back() << endl;
    cout << "Deque size: " << dq.size() << endl;

    dq.pop_front();
    cout << "Front element after pop_front: " << dq.front() << endl;
    cout << "Deque size after pop_front: " << dq.size() << endl;

    dq.pop_back();
    cout << "Back element after pop_back: " << dq.back() << endl;
    cout << "Deque size after pop_back: " << dq.size() << endl;

    return 0;
}
