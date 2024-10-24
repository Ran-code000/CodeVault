#include <iostream>
#include <vector>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//回文链表 ———— LCR027
//法一： 双指针
//时间空间复杂度均为 O(n)
bool isPalindrome(ListNode* head){
    if(head == nullptr || head->next == nullptr) return true;
    vector<int> v;
    ListNode* curr = head;
    while(curr) v.push_back(curr->val);
    int i = 0, j = v.size() - 1;
    while(i < j){
        if(v[i] != v[j]) return false;
        i++, j--;
    }
    return true;
}
//法二：递归（一个不是很好但可以更了解递归的方法）
//时间空间复杂度均为 O(n)
ListNode* frontNode = nullptr;
bool CheckPalindrome(ListNode* head){
    if(head){
        if(!CheckPalindrome(head->next)) return false;
        if(head->val != frontNode->val) return false;
        frontNode = frontNode->next;
        return true;
    }
}
bool isPalindrome(ListNode* head){
    ListNode* frontNode = head;
    CheckPalindrome(head);
}
//法三：快慢指针 + 反转链表
//最优：时间复杂度 O(n)、空间复杂度 O(1)
ListNode* reverseLinklist(ListNode* head){
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* dum = new ListNode(0);
    dum->next = head;
    ListNode* p = dum->next;
    ListNode* q = p->next;
    while(p && q){
        p->next = q->next;
        q->next = dum->next;
        dum->next = q;
        q = p->next;
    }
    //return dum->next;
    ListNode* reversedHead = dum->next;
    delete dum; // 释放哑节点的内存
    return reversedHead;
}
ListNode* FindEndOfFirstHalf(ListNode* head){
    ListNode* slow = head, *fast = head;
    while(fast && fast->next){
        fast = fast->next->next;
        if(fast == nullptr) break; // 链表长度为奇数时，fast 会停在中间节点
        slow = slow->next;
    }
    return slow;
}

bool isPalindrome(ListNode* head){
    if(head == nullptr || head->next == nullptr) return true;
    ListNode* firstHalfEnd = FindEndOfFirstHalf(head);
    ListNode* secondHalfStart = reverseLinklist(firstHalfEnd->next);

    ListNode* pa = head;
    ListNode* pb = secondHalfStart;
    bool _ispalindrome = true;
    while(pb){
        if(pa->val != pb->val) _ispalindrome = false;
        pa = pa->next;
        pb = pb->next;
    }
    firstHalfEnd->next = reverseLinklist(secondHalfStart); // 恢复原链表结构
    return _ispalindrome;
}