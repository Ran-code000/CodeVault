#include <iostream>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//设计链表 ———— LCR707
//法一：单链表（具体实现见D:\DataStructure\MyClass\MyLinklist\Code\win3_add leftshift.cpp）
//法二：双向链表（添加哨兵头节点和尾节点）
struct Listnode{
    int val;
    Listnode* next, *prev;
};
class MyLinkedList {
    Listnode* head, *tail;
    int size;//链表实际长度
public:
    MyLinkedList() : size(0){  
        //创建哨兵头节点和尾节点
        head = new Listnode(0);
        tail = new Listnode(0);
        head->next = tail;
        tail->prev = head;      
    }
    int get(int index) {
        if(index >= size || index < 0) return -1;

        //比较从 head 还是 tail 来遍历会比较快找到目标，然后进行遍历
        Listnode* curr;
        if(index << 1 < size){
            curr = head;
            for(int i = 0; i <= index; i++) curr = curr->next;
        }else{
            curr = tail;
            for(int i = 0; i <= size - 1 - index; i++) curr = curr->prev;
        }
        return curr->val;
    }
    void addAtHead(int val){ addAtIndex(0, val);}
    void addAtTail(int val){ addAtIndex(size, val);}
    void addAtIndex(int index, int val) {
        if(index > size) return;
        index = max(0, index);

        //比较从 head 还是 tail 来遍历会比较快找到目标，然后进行遍历
        Listnode* newnode = new Listnode(val);
        Listnode* curr, *prev;
        if(index << 1 < size){
            prev = head;
            //因为带哨兵头节点，所以'<' prev 刚好到目标位置的前一个
            for(int i = 0; i < index; i++) prev = prev->next;
            curr = prev->next; 
        }else{
            curr = tail;
            //因为带哨兵尾节点，所以'<' curr 刚好到目标位置的前一个, 则'<=' curr 刚好到目标位置
            for(int i = 0; i <= size - 1 - index; i++) curr = curr->prev;
            prev = curr->prev;
        }
        //因为头尾都带哨兵节点，所以不用判空
        newnode->prev = prev;
        newnode->next = curr;
        prev->next = newnode;
        curr->prev = newnode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index >= size || index < 0) return;

        //比较从 head 还是 tail 来遍历会比较快找到目标，然后进行遍历
        Listnode* curr, *prev;
        if(index << 1 < size){
            prev = head;
            for(int i = 0; i < index; i++) prev = prev->next;
            curr = prev->next;
        }else{
            curr = tail;
            for(int i = 0; i <= size - 1 - index; i++) curr = curr->prev;
            prev = curr->prev;
        }
        //因为头尾都带哨兵节点，所以不用判空
        prev->next = curr->next;
        curr->next->prev = prev;
        delete curr;
        size--;
    }
    
};
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */