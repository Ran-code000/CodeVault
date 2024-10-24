#include <iostream>
#include <unordered_map>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
//复杂链表的复制 ———— LCR154
//法一：哈希表
//时间复杂度 O(n)、空间复杂度 O(n)
Node* copyRandomList(Node* head){
    if(head == nullptr) return nullptr;
    //建立原节点到新节点的映射
    unordered_map<Node*, Node*> um;
    //构建新链表的 next 和 random 指向
    Node* curr = head;
    while(curr) um[curr] = new Node(curr->val), curr = curr->next;
    curr = head;
    while(curr) um[curr]->next = um[curr->next], um[curr]->random = um[curr->random], curr = curr->next;
    //发挥新链表的头节点
    return um[head];
}
//法二：拼接 + 拆分
//考虑构建 原节点 1 -> 新节点 1 -> 原节点 2 -> 新节点 2 -> …… 的拼接链表，如此便可在访问原节点的 random 指向节点的同时找到新对应新节点的 random 指向节点。
// 算法流程：
// 1. 复制各节点，构建拼接链表:
// 2. 构建新链表各节点的 random 指向：
//    当访问原节点 cur 的随机指向节点 cur.random 时，对应新节点 cur.next 的随机指向节点为 cur.random.next 。
// 3. 拆分原 / 新链表：
//    设置 pre / cur 分别指向原 / 新链表头节点，遍历执行 pre.next = pre.next.next 和 cur.next = cur.next.next 将两链表拆分开。
// 4. 返回新链表的头节点 res 即可。
Node* copyRandomList(Node* head) {
    if(head == nullptr) return nullptr;
    Node* cur = head;
    // 1. 复制各节点，并构建拼接链表
    while(cur != nullptr) {
        Node* tmp = new Node(cur->val);
        tmp->next = cur->next;
        cur->next = tmp;
        cur = tmp->next;
    }
    // 2. 构建各新节点的 random 指向
    cur = head;
    while(cur != nullptr) {
        if(cur->random != nullptr)
            cur->next->random = cur->random->next;
        cur = cur->next->next;
    }
    cur = head->next;
    Node* pre = head, *res = head->next;
    while(cur->next != nullptr) {
        pre->next = pre->next->next;
        cur->next = cur->next->next;
        pre = pre->next;
        cur = cur->next;
    }
    pre->next = nullptr; // 单独处理原链表尾节点
    return res;      // 返回新链表头节点
}
Node* copyRandomList(Node* head){
    if(head == nullptr) return nullptr;
    // 1. 复制各节点，并构建拼接链表
    Node* curr = head;
    while(curr){
        Node* temp = new Node(curr->val);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
    // 2. 构建各新节点的 random 指向
    curr = head;
    while(curr){
        if(curr->random) curr->next->random = curr->random->next;
        curr = curr->next->next;
    }
    // 3. 拆分两链表
    Node* pa = head, *pb = head->next, *res = pb;
    while(pb && pb->next){
        pa->next = pa->next->next;
        pb->next = pb->next->next;
        pa = pa->next;
        pb = pb->next;
    }
    //!!! 单独处理原链表尾节点
    // 假设：原链表：1 -> 2 -> 3 -> nullptr；拼接后的链表：1 -> 1' -> 2 -> 2' -> 3 -> 3' -> nullptr
    // 如果没有 pa->next = nullptr; 来处理原链表的尾节点，原链表的最后一个节点将继续指向新链表中的节点
    // 拆分后，原链表可能变成 1 -> 2 -> 3 -> 3' -> nullptr
    // 这样，原链表的尾节点 3 仍然指向新链表中的复制节点 3'，它不再是链表的尾节点，导致两个链表相互连接，会形成循环引用。
    pa->next = nullptr;
    // 4. 返回新链表头节点
    return res;
}