#include <iostream>

using namespace std;
class Stack{
    struct ListNode{
        int val;
        struct ListNode* next;
    };
public:
    Stack(const Stack &a) = delete;
    Stack& operator = (const Stack& other) = delete;
    ~Stack(){
        clear();
    }
    void push(int val){
        ListNode *node = new ListNode;
        node -> val = val;
        node -> next = head;
        head = node;
    }
    void pop(){
        while(!isempty()){
            ListNode *node = head;
            head = head -> next;
            delete node;
        }
    }
    int top(){
        if(!isempty()) return head -> val;
        throw runtime_error("Accessing empty stack.");
    }
    bool isempty(){
        return !head;
    }
    void clear(){
        while(!isempty()) pop();
    }
    void print(){
        for(ListNode *p = head; p != nullptr; p = p -> next) cout << p -> val << ",";
    }
private:
    ListNode *head = nullptr;
    
};
int main(){

    return 0;
}