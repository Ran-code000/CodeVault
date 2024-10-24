#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//合并 k 个有序链表 ———— LCR078
//法一：顺序合并
// 时间复杂度：假设每个链表的最长长度是 n。在第一次合并后，ans 的长度为 n；第二次合并后，ans 的长度为 2×n，第 i 次合并后，ans 的长度为 i×n。
// 第 i 次合并的时间代价是 O(n+(i−1)×n) = O(i×n)，总的时间代价为 O(∑i=1 k (i×n)) = O(（(1+k)⋅k/2）×n)=O(k^2 *n)，
// 故渐进时间复杂度为 O(k^2 *n)。
// 空间复杂度：没有用到与 k 和 n 规模相关的辅助空间，故渐进空间复杂度为 O(1)。
ListNode* mergeTwoLists(ListNode *a, ListNode *b){
    //没有这句代码时，程序并不会必然报错，但可能导致逻辑上的混乱或效率低下。如果 a 和 b 中有任意一个为空，合并操作应该立刻返回另一个非空链表，从而简化后续处理。
    if((!a) || (!b)) return a ? a : b;

    ListNode* pc = new ListNode(0), *res = pc, *pa = a, *pb = b;
    while(pa && pb){
        if(pa->val <= pb->val) pc->next = pa, pa = pa->next;
        else pc->next = pb, pb = pb->next;
        pc = pc->next;
    }
    pc->next = (pa ? pa : pb);
    return res->next;
}
ListNode* mergeKLists(vector<ListNode*>& lists){
    ListNode *ans = nullptr;
    for(size_t i = 0; i < lists.size(); i++) ans = mergeTwoLists(ans, lists[i]);
    return ans;
}
//法二：分治合并
// 时间复杂度：考虑递归「向上回升」的过程——第一轮合并 2/k 组链表，每一组的时间代价是 O(2n)；
// 第二轮合并 4/k 组链表，每一组的时间代价是 O(4n)......所以总的时间代价是 O(∑i=1 k/2^i * 2^i * n) = O(kn×logk)，
// 故渐进时间复杂度为 O(kn×logk)。
// 空间复杂度：递归会使用到 O(logk) 空间代价的栈空间

ListNode* mergeTwoLists(ListNode *a, ListNode *b){
    if(!a || !b) return a ? a : b;
    ListNode* pc = new ListNode(0), *res = pc, *pa = a, *pb = b;
    while(pa && pb){
        if(pa->val <= pb->val) pc->next = pa, pa = pa->next;
        else pc->next = pb, pb = pb->next;
        pc = pc->next;
    }
    pc->next = (pa ? pa : pb);
    return res->next;
}
ListNode* merge(vector <ListNode*> &lists, int l, int r) {
    if(l == r) return lists[l];
    if(l > r) return nullptr;
    int mid = (l + r) >> 1;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}
ListNode* mergeKLists(vector<ListNode*>& lists){ return merge(lists, 0, lists.size() - 1);}
/*
Example Linked Lists
List 1: 1 → 4 → 5
List 2: 1 → 3 → 4
List 3: 2 → 6
List 4: 0 → 7
List 5: 8 → 9
Step-by-Step Explanation of the Code
Input Preparation: Create a vector of linked lists: vector<ListNode*> lists = {list1, list2, list3, list4, list5};

Calling mergeKLists: You start by calling mergeKLists(lists):

This will internally call merge(lists, 0, 4) (where 0 is the index of the first list and 4 is the index of the last list).

First Call to merge:
Here, l = 0 and r = 4. Since l is not equal to r, it calculates mid = 2.
It then recursively calls merge(lists, 0, 2) for the left half.

Second Call to merge (Left Half):
Now l = 0, r = 2. Calculate mid = 1.
Call merge(lists, 0, 1).

Third Call to merge (Further Left):
Now l = 0, r = 1. Calculate mid = 0.
Call merge(lists, 0, 0) which returns list1 (1 → 4 → 5).

Back to Third Call:
Now call merge(lists, 1, 1) which returns list2 (1 → 3 → 4).
Now you call mergeTwoLists with the results from the two calls:
Merging List 1 and List 2: mergeTwoLists(list1, list2);
1 (from List 1) → 1 (from List 2) → 3 → 4 → 4 → 5
Resulting merged list: 1 → 1 → 3 → 4 → 4 → 5.

Back to Second Call:
Call merge(lists, 2, 2) which returns list3 (2 → 6).
Now merge the results of previous merge (1 → 1 → 3 → 4 → 4 → 5) with List 3:
Merging (First Three Lists): mergeTwoLists(merged_list_from_1_and_2, list3);
Result: 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6.

Back to First Call
Now call merge(lists, 3, 4).
Here l = 3, r = 4. Calculate mid = 3.
Call merge(lists, 3, 3) which returns list4 (0 → 7).
Call merge(lists, 4, 4) which returns list5 (8 → 9).
Merge these two lists: mergeTwoLists(list4, list5);
Result: 0 → 7 → 8 → 9.

Final Merge:
Now merge the result from the previous steps (1 → 1 → 2 → 3 → 4 → 4 → 5 → 6) with (0 → 7 → 8 → 9):
Final Merging Result: mergeTwoLists(merged_list_of_first_three, merged_list_of_last_two);

Final merged list:
0 → 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6 → 7 → 8 → 9.
Final Output
The final output is a single sorted linked list:
*/
//法三：使用优先队列合并
// 时间复杂度：考虑优先队列中的元素不超过 k 个，那么插入和删除的时间代价为 O(logk)，这里最多有 kn 个点，对于每个点都被插入删除各一次，故总的时间代价即渐进时间复杂度为 O(kn×logk)。
// 空间复杂度：这里用了优先队列，优先队列中的元素不超过 k 个，故渐进空间复杂度为 O(k)
// priority_queue 默认是最大堆。要创建最小堆，可以重载小于运算符，或者使用自定义比较器
// 使用自定义比较器
struct node{
    int val;
    ListNode* p;
    node(int val = 0, ListNode* p = nullptr) : val(val), p(p){}
};
struct COMP{
    bool operator()(const node& a, const node& b){ return a.val > b.val;}
};
priority_queue<node, vector<node>, COMP> pq;
ListNode* mergeKLists(vector<ListNode*>& lists){
    //注意，这里不能直接用 pq.push({0, nullptr}), 因为后面要用到 list->next 的值，所以要先把 list 转成 node，再放入 pq
    for(auto list : lists) if(list) pq.push({list->val, list});
    ListNode* head = new ListNode(0), *curr = head;
    while(!pq.empty()){
        auto temp = pq.top(); pq.pop();
        head->next = temp.p;
        head = head->next;
        if(temp.p->next) pq.push({temp.p->next->val, temp.p->next});
    }
    return curr->next;
}
// 使用重载小于运算符
struct node{
    int val;
    ListNode* p;
    node(int val = 0, ListNode* p = nullptr) : val(val), p(p){}
    // 错误写法 bool operator < (const node& a){ return val > a->val;}
    bool operator < (const node& a) const { return val > a.val;}
    /* 
    不加 const 会导致编译错误，在 C++ 中，成员函数默认不被视为常量函数。当尝试调用 operator< 时，如果左侧对象是常量，编译器会找不到非 const 的版本。
    总结：加上 const 表示该函数不会修改对象状态，允许在常量对象上调用，不加 const 会导致无法在常量对象上使用，造成编译错误。
    */
};
priority_queue<node> pq;
ListNode* mergeKLists(vector<ListNode*>& lists){
    //注意，这里不能直接用 pq.push({0, nullptr}), 因为后面要用到 list->next 的值，所以要先把 list 转成 node，再放入 pq
    for(auto list : lists) if(list) pq.push({list->val, list});
    ListNode* head = new ListNode(0), *curr = head;
    while(!pq.empty()){
        auto temp = pq.top(); pq.pop();
        head->next = temp.p;
        head = head->next;
        if(temp.p->next) pq.push({temp.p->next->val, temp.p->next});
    }
    return curr->next;
}