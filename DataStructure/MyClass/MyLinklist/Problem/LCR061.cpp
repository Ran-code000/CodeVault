#include <iostream>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//旋转链表 ———— LCR061
//法一：闭合为环
//闭环 ———— 找新断点（新头节点）———— 断环
ListNode* rotateRight(ListNode* head, int k) {
    if(k == 0 || head == nullptr || head->next == nullptr) return head;
    //计算链表长度
    ListNode* curr = head;
    int len = 1;
    while(curr->next) curr = curr->next, len++; 
    //闭合
    curr->next = head;
    //找到新链表的最后一个节点（即原链表的第 len − (k % len) 个节点）
    int offset = len - k % len;
    if(offset == 0) return head;
    while(offset--) curr = curr->next;
    //将当前闭合为环的链表断开
    ListNode* newhead = curr->next;
    curr->next = nullptr;
    return newhead;
}