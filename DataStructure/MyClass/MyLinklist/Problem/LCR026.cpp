#include <iostream>
#include <vector>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//重排链表 ———— LCR026
// L0 → L1 → … → Ln-1 → Ln 请将其重新排列后变为：
// L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
// 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

//法一： 线性表（类比D:\DataStructure\MyClass\MyLinklist\Problem\LCR023.cpp中，用哈希表存储节点信息后遍历（if visited.count()）实现找到链表节点）
//因为链表不支持下标访问，所以我们无法随机访问链表中任意位置的元素。

// emplace_back 
// 1.用法
// emplace_back 是 vector 提供的成员函数，用于在容器的末尾直接构造元素，而不是复制或移动现有的元素。这与 push_back 有类似功能，但有些细微区别。
// 2.原理
// (1)高效构造：emplace_back 直接在容器的内存中构造新对象，而不需要像 push_back 创建一个临时对象然后复制或移动它。可以避免不必要的临时对象构造，提升性能。
// (2)完美转发：emplace_back 使用 C++11 的 完美转发（perfect forwarding），即可以将传入的参数原封不动地传递给新元素的构造函数。
//          意味着可以在调用 emplace_back 时，直接传递构造函数的参数，容器会在内部使用这些参数构造新元素。
// 3.区别
// push_back(node)：会先创建 node，然后将它复制（或移动）到 vector 中。
// emplace_back(node)：会直接在 vector 内存中构造 node，避免了额外的复制或移动操作。
// 4.代码示例
/*
vector<string> vec;

// 使用 push_back（需要构造临时对象）
string str = "hello";
vec.push_back(str);  // 复制 str
vec.push_back("world");  // 创建临时对象然后复制

// 使用 emplace_back（直接构造）
vec.emplace_back("hello");  // 直接在 vector 内部构造 "hello"
*/
void reorderList(ListNode *head){
    if(head == nullptr) return;
    vector<ListNode*> v;
    ListNode* curr = head;
    while(curr) v.emplace_back(curr), curr = curr->next;
    int i = 0, j = v.size() - 1;
    while(i < j){
        v[i]->next = v[j], i++;
        if(i == j) break;
        v[j]->next = v[i], j--;
    }
    v[i]->next = nullptr;//i 指向最后一个处理的节点。当 i 达到 j 时，它实际上指向链表的最后一个节点
    //将链表的最后一个节点的 next 指针设为 nullptr，从而标识链表的结束。
}

//法二：寻找链表中点 + 链表逆序 + 合并链表
void reorderList(ListNode *head){
    if(head == nullptr || head->next == nullptr) return;
    //找中点
    //详见 LCR077.cpp 57行；LCR077details.cpp 29行
    //！！！！更新：最优方法见 LCR026details.cpp
    //如果链表长度是 偶数，slow 会指向中间靠后的节点
    ListNode* slow = head, *fast = head, *mid;
    while(fast && fast->next){
        fast = fast->next->next;
        if(fast == nullptr) break;
        slow = slow->next;
    }
    mid = slow->next;
    slow->next = nullptr;//断开前半部分链表
    //链表逆序
    ListNode* dum = new ListNode(0);
    dum->next = mid;
    ListNode* p = dum->next;
    ListNode* q = p->next;
    while(p && q){
        p->next = q->next;
        q->next = dum->next;
        dum->next = q;
        q = p->next;
    }
    mid = dum->next;
    //由于接下来的逆序操作会改变链表的连接方式，原始的中间节点（mid）将不再指向正确的节点, 需要 mid 指向开始保存的中间节点（dum->next）
    //合并
    ListNode* pa = head, *pb = mid;
    ListNode* pc = new ListNode(0);
    ListNode* res = pc;
    while(pa && pb){
        pc->next = pa, pa = pa->next, pc = pc->next;
        pc->next = pb, pb = pb->next, pc = pc->next;
    }
    pc->next = pa ? pa : pb;
    ListNode* temp = res;
    res = res->next;
    delete temp;
}