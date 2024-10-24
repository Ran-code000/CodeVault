#include <iostream>

struct ListNode {
    int value;       // 节点存储的数据
    ListNode* next;  // 指向下一个节点的指针

    ListNode(int val) : value(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;  // 指向链表第一个节点的指针

public:
    LinkedList() : head(nullptr){}  // 构造函数，初始化为空链表

    ~LinkedList();  // 析构函数，用于释放链表的内存

    void append(int value);  // 在链表末尾添加一个节点
    void insert(int value, int position);  // 在指定位置插入一个节点
    void remove(int value);  // 删除链表中第一个值为value的节点
    void display() const;  // 打印链表
    ListNode* find(int value);  // 查找值为value的节点
};

LinkedList::~LinkedList() {
    ListNode* curr;
    while(head){
        curr = head;
        head = head->next;
        delete curr;
    }
}

void LinkedList::append(int value) {
    ListNode* newNode = new ListNode(value);//创建一个新节点
    if (head == nullptr) head = newNode;
    else {
        ListNode* current = head;
        while (current->next != nullptr) current = current->next;
        current->next = newNode;
    }
}

void LinkedList::insert(int value, int position) {
    ListNode* newNode = new ListNode(value);//创建新节点
    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        ListNode* prev = nullptr;
        ListNode* current = head;
        int index = 0;
        while (current != nullptr && index < position) {
            prev = current;
            current = current->next;
            index++;
        }
        newNode->next = current;
        if (prev != nullptr) prev->next = newNode;
    }
}

void LinkedList::remove(int value) {
    ListNode* current = head;
    ListNode* prev = nullptr;

    while (current != nullptr && current->value != value) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;  // 没找到值为value的节点

    if (prev == nullptr) head = head->next;  // 要删除的是头节点
    else prev->next = current->next;

    delete current;
}

void LinkedList::display() const {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

ListNode* LinkedList::find(int value) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->value == value) return current;
        current = current->next;
    }
    return nullptr;
}

int main() {
    LinkedList list;
    list.append(5);
    list.append(10);
    list.insert(3, 0);  // 在头部插入3
    list.display();     // 输出链表
    list.remove(10);    // 删除值为10的节点
    list.display();     // 再次输出链表

    return 0;
}
