#include <iostream>
#include <unordered_set>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//相交链表 ———— LCR023
//法一： 哈希集合
//首先遍历链表 headA，并将链表 headA 中的每个节点加入哈希集合 unordered_set<> 中。
//然后遍历链表 headB，对于遍历到的每个节点，判断该节点是否在哈希集合中
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB){
    unordered_set<ListNode*> visited; //去重，随机
    ListNode* temp = headA;
    while(temp != nullptr){
        visited.insert(temp);
        temp = temp->next;
    }
    temp = headB;
    while(temp != nullptr){
        if(visited.count(temp)) return temp; //unordered_set<> 用.count()方法判断是否存在，因为哈希集合 unordered_set<>是去重的
        temp = temp->next;
    }
    return nullptr;
}

//法二： 双指针法
//情况一：两个链表相交
// 链表 headA 和 headB 的长度分别是 m 和 n。
// 假设链表 headA 的不相交部分有 a 个节点，链表 headB 的不相交部分有 b 个节点，两个链表相交的部分有 c 个节点，
// 则有 a+c=m，b+c=n。

// 如果 a=b，则两个指针会同时到达两个链表相交的节点，此时返回相交的节点；
// 如果 a!=b，则指针 pA 会遍历完链表 headA，指针 pB 会遍历完链表 headB，两个指针不会同时到达链表的尾节点
//           然后指针 pA 移到链表 headB 的头节点，指针 pB 移到链表 headA 的头节点，然后两个指针继续移动
//           在指针 pA 移动了 a+c+b 次、指针 pB 移动了 b+c+a 次之后，两个指针会同时到达两个链表相交的节点
//           该节点也是两个指针第一次同时指向的节点，此时返回相交的节点。

// 情况二：两个链表不相交
// 链表 headA 和 headB 的长度分别是 m 和 n。考虑当 m=n 和 m!=n 时，两个指针分别会如何移动：

// 如果 m=n，则两个指针会同时到达两个链表的尾节点，然后同时变成空值 null，此时返回 null；
// 如果 m!=n，则由于两个链表没有公共节点，两个指针也不会同时到达两个链表的尾节点，因此两个指针都会遍历完两个链表，
//            在指针 pA 移动了 m+n 次、指针 pB 移动了 n+m 次之后，两个指针会同时变成空值 null，此时返回 null。
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
    if(headA == nullptr || headB == nullptr) return nullptr;
    ListNode* pa = headA, *pb = headB;
    while(pa != pb){
        pa = (pa == nullptr)? headB : pa->next;
        pb = (pb == nullptr)? headA : pb->next;
        //wrong : 在检查指针是否为 nullptr 时直接更新指针，而不是先访问它们的 next 属性
        //如果 pa 或 pb 当前指向 nullptr，下一次循环将会访问它们的 next 属性，这可能会导致程序崩溃。具体来说，如果 pa 或 pb 为 nullptr, 会在 pa->next 或 pb->next 的情况下引发空指针解引用。
        //pa = (pa->next == nullptr) ? headB : pa->next;
        //pb = (pb->next == nullptr) ? headA : pb->next; 
    }
    return pa;
}