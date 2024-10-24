#include <iostream>
using namespace std;
struct Listnode{
    int val;
    Listnode *next;
    Listnode(int val, Listnode *p = nullptr) : val(val), next(p){};
};

class List{
    Listnode* head;
public:
    void append(int val);
    void insert(int pos, int val);
    void remove(int val);
    void display();
    Listnode* find(int val);
    List() : head(nullptr){};
    ~List();
};
List::~List(){
    Listnode* current = head;
    while(current != nullptr){
        Listnode* next = current->next;
        delete current;
        current = next;
    }
}
void List::append(int val){
    Listnode *newnode = new Listnode(val);
    if(head == nullptr) head = newnode;
    else{
        Listnode* current = head;
        while(current->next != nullptr) current = current->next;
        current->next = newnode;
    }
}
void List::insert(int pos, int val){
    Listnode *newnode = new Listnode(val);
    int id = 0;
    if(pos == 0){
        newnode->next = head;
        head = newnode;
    }else{
        Listnode *prev = nullptr, *current = head;
        while(current != nullptr && id < pos){
            prev = current;
            current = current->next;
            id++;
        }
        newnode->next = current;
        if(prev != nullptr) prev->next = newnode;
    }
}

void List::remove(int val){
    Listnode *prev = nullptr, *current = head;
    while(current != nullptr && current->val != val){
        prev = current;
        current = current->next;
    }
    if(current == nullptr) return;
    if(prev == nullptr) head = head->next;
    else prev->next = current->next;
    delete current;
}

Listnode* List::find(int val){
    Listnode* current = head;
    while(current != nullptr){
        if(current->val == val) return current;
        current = current->next;
    }
    return nullptr;
}
void List::display(){
    Listnode* current = head;
    while(current != nullptr){
        cout << current->val << " -> ";
        current = current->next;
    }
    cout << "nullptr" << "\n";
}

int main(){
    List list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.display();
    list.insert(2, 99);
    list.insert(5, 999);
    list.display();
    list.find(99);
    list.remove(4);
    list.display();

    return 0;
}    
