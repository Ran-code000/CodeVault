#include <iostream>
#include <unordered_set>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//环形链表 ———— LCR022
//法一：哈希表
//时间空间复杂度均为 O(n)   
ListNode *detectCycle(ListNode *head){
    unordered_set<ListNode*> us;
        ListNode* curr = head;
        while(curr){
            us.insert(curr), curr = curr->next;
            if(us.count(curr)) return curr;
        }
        return nullptr;
}
//法二：快慢指针
//时间复杂度 O(n)、空间复杂度 O(1)
//设链表中环外部分的长度为 a。slow 指针进入环后，又走了 b 的距离与 fast 相遇。
//此时，fast 指针已经走完了环的 n 圈，因此它走过的总距离为 a+n(b+c)+b=a+(n+1)b+nc。
//任意时刻，fast 走过的距离都为 slow 的 2 倍。因此，a+(n+1)b+nc=2(a+b)⟹a=c+(n−1)(b+c)
//有了 a=c+(n−1)(b+c) 的等量关系，发现：从相遇点到入环点的距离加上 n−1 圈的环长，恰好等于从链表头部到入环点的距离。
//因此，当发现 slow 与 fast 相遇时，再额外使用一个指针 ptr。起始，它指向链表头部；
//随后，它和 slow 每次向后移动一个位置。最终，它们会在入环点相遇。
ListNode *detectCycle(ListNode *head){
    if(head == nullptr || head->next == nullptr) return nullptr;
    ListNode* slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        //相遇时 slow 和 fast 都在距离环的入口 b（顺时针）的位置处，需要再走 c 到达环的入口
        //a=c+(n−1)(b+c) ———— p 走过 a ，slow 走过 c + (n-1)(b + c)
        if(slow == fast){
            ListNode* p = head;
            while(p != slow) p = p->next, slow = slow->next;
            return p;
        }
    }
    return nullptr;
}
