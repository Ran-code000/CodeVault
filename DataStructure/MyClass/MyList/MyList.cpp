#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class MyList {
private:
    struct Node {
        T val;
        Node* next;
        Node* prev;
        Node(const T& v) : val(v), next(nullptr), prev(nullptr){}
    };
    Node* head;
    Node* tail;
    size_t sz;
public:
    MyList() : head(nullptr), tail(nullptr), sz(0) {}
    ~MyList(){ clear();}
    MyList(const MyList& other) : head(nullptr), tail(nullptr), sz(0) {
        for(Node* curr = other.head; curr != nullptr; curr = curr->next) push_back(curr->val);
    }
    MyList(MyList&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }
    MyList& operator=(const MyList& other){
        if(this == &other) return *this;
        else{
            clear();
            for (Node* curr = other.head; curr != nullptr; curr = curr->next) push_back(curr->val);
        }
        return *this;
    }
    MyList& operator=(MyList&& other) noexcept {
        if(this == &other) return *this;
        else{
            clear();
            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0;
        }
        return *this;
    }
    size_t size() const { return sz;}
    bool empty() const { return sz == 0;}
    void push_front(const T& v) {
        Node* new_node = new Node(v);
        if (empty()) head = tail = new_node;
        else{
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        sz++;
    }
    void push_back(const T& v) {
        Node* new_node = new Node(v);
        if (empty()) head = tail = new_node;
        else{
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        sz++;
    }
    void pop_front() {
        if (empty()) throw out_of_range("List is empty");
        else if(size() == 1) delete head, head = tail = nullptr, sz = 0;
        else{
            Node* temp = head;
            head = head->next;
            delete temp;
            head->prev = nullptr; //同理
            sz--;
        }
    }
    void pop_back() {
        if (empty()) throw out_of_range("List is empty");
        else if(size() == 1) delete tail, head = tail = nullptr, sz = 0;
        else{
            Node* temp = tail;
            tail = tail->prev;
            delete temp;
            //若新的 tail 的 next 指针没有被设置为 nullptr 会导致迭代器在遍历链表时陷入无限循环，
            //因为之前的结点指针仍然指向已删除的结点。
            tail->next = nullptr;
            sz--;
        }
    }
    void clear() { while (!empty()) pop_front();}

    class iterator {
    private:
        Node* curr;
    public:
        iterator(Node* node) : curr(node) {}
        T& operator*(){ return curr->val;}
        iterator& operator++() {
            curr = curr->next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            curr = curr->next;
            return temp;
        }
        iterator& operator--() {
            if(curr) curr = curr->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator temp = *this;
            if(curr) curr = curr->prev;
            return temp;
        }
        bool operator==(const iterator& other) const {
            return curr == other.curr;
        }
        bool operator!=(const iterator& other) const {
            return curr != other.curr;
        }
    };
    iterator begin(){ return iterator(head);}
    iterator end(){ return iterator(nullptr);}
    const iterator begin() const { return iterator(head);}
    const iterator end() const { return iterator(nullptr);}
};

int main(){
    MyList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    std::cout << "Elements: ";
    for(auto it = lst.begin(); it != lst.end(); it++) std::cout << *it << " ";
    std::cout << std::endl;

    lst.pop_front();
    std::cout << "After pop_front, elements: ";
    for(auto it = lst.begin(); it != lst.end(); it++) std::cout << *it << " ";
    std::cout << std::endl;

    lst.pop_back();
    std::cout << "After pop_back, elements: ";
    for(auto it = lst.begin(); it != lst.end(); it++) std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
