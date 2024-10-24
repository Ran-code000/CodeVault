#include <iostream>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//链表排序 ———— LCR077
//这道题考虑时间复杂度优于 O(n^2) 的排序算法。
//题目的进阶问题要求达到 O(nlogn) 的时间复杂度和 O(1) 的空间复杂度，
//时间复杂度是 O(nlogn) 的排序算法包括归并排序、堆排序和快速排序（快速排序的最差时间复杂度是 O(n^2)），
//其中最适合链表的排序算法是归并排序。
//归并排序基于分治算法。最容易想到的实现方式是自顶向下的递归实现，考虑到递归调用的栈空间
//自顶向下归并排序的空间复杂度是 O(logn)。 见法一
//如果要达到 O(1) 的空间复杂度，则需要使用自底向上的实现方式。见法二
//法一：自顶向下归并排序
//合并（归并排序的夫妻操作）
ListNode* merge(ListNode* head1, ListNode* head2){
    ListNode* pc = new ListNode(0);
    ListNode* pa = head1, *pb = head2;
    ListNode* res = pc;
    while(pa && pb){
        if(pa->val <= pb->val) pc->next = pa, pa = pa->next;
        else pc->next = pb, pb = pb->next;
        pc = pc->next;
    }
    pc->next = pa == nullptr ? pb : pa;
    return res->next;
}
//归并排序
ListNode* _sortList(ListNode* head, ListNode* tail){
    //有 tail 参数时的错误代码；若执行第 51 行代码则这个判断条件是正确的
    //if(head == nullptr || head->next == nullptr) return head; 
    //假设链表为 1 -> 2 -> 3 -> 4，_sortList 递归地处理这个链表，
    //在某次递归调用中，假设 head 指向 1，但此时 tail 指向 2，而不是 nullptr。
    //如果不考虑 tail，链表会被错误地进一步分割，导致 1 和 2 之间的分割不明确，从而可能使递归处理无法正确停止
    //正确代码
    if(head == nullptr) return head;
    if(head->next == tail) {head->next = nullptr; return head;}
    //将 head 的 next 指针置为 nullptr，为了防止后续递归中的 tail 干扰，确保当前递归处理的链表是独立的一段。
    //当链表被分割到只剩一个节点时，即 head->next == tail 时，直接返回该节点，if (head->next == tail) 确保在链表被分割到只剩一个节点时停止递归。

    //快慢指针找中点 ———— 归并排序的分界点
    ListNode* slow = head, *fast = head;
    //细节探索：
    //法一（不太健壮但针对这个代码也能过，原因见 LCR077details.cpp）
    // while(fast != tail){
    //     slow = slow->next;
    //     fast = fast->next;
    //     if(fast != tail) fast = fast->next;
    // }
    //法二（更加健壮）
    while(fast != tail && fast->next != tail){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* mid = slow;//若链表长度为偶数，最后 slow 指针指向中点的后一个节点；若链表长度为奇数，最后 slow 指针指向中点。因为区间左闭右开，所以链表归并分割正确
    //若加一句 min->next = nullptr, 则 tail 参数可以不要 
    //区间左闭右开 (右边 tail == nullptr 恒成立)
    return merge(_sortList(head, mid), _sortList(mid, tail));
}
ListNode* sortList(ListNode* head){
    return _sortList(head, nullptr); //使用归并排序
}

//法二：自底向上归并排序
//用 subLength 表示每次需要排序的子链表的长度，初始时 subLength=1。
//每次将链表拆分成若干个长度为 subLength 的子链表（最后一个子链表的长度可以小于 subLength）
//按照每两个子链表一组进行合并，合并后即可得到若干个长度为 subLength×2 的有序子链表（最后一个子链表的长度可以小于 subLength×2）。
//将 subLength 的值加倍，重复第 2 步，对更长的有序子链表进行合并操作，直到有序子链表的长度大于或等于 length，整个链表排序完毕。

ListNode* sortList(ListNode* head){
   if(head == nullptr || head->next == nullptr) return head;
   //得到链表长度
    int length = 0;
    ListNode* plen = head;
    while(plen) plen = plen->next, length++;
    //方便处理头节点的变化，添加哨兵节点，指向链表的第一个有效节点，即 dum->next = head; (head 可能改变所以不能直接用 head)
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    //自底向顶归并，遍历可能的子区间划分单位
    for(int sublength = 1; sublength < length; sublength <<= 1){
        ListNode* prev = dummy;
        //ListNode* curr = head; 错误
        //如果你 ListNode* curr = head;，那么直接从原始链表的头节点开始处理。排序会导致需要对头节点的改变
        //引入哨兵节点后，dum 的 next 总是指向链表的第一个有效节点。这样，无论链表头节点是否会被修改，链表的整体结构都可以通过哨兵节点来安全处理。
        //prev 依赖于哨兵节点，prev 开始时是哨兵节点 dum，如果从 head 开始操作，可能会导致丢失链表的头节点，或者对链表头处理不当。
        ListNode* curr = dummy->next; 
        //在给定的划分单位长度下，用双指针遍历链表实现从左到右区间的划分
        while(curr){
            //第一个区间的起始位置
            ListNode* head1 = curr;
            //找第一个区间的终止位置
            //注意 curr->next 判断条件为了对空指针解引用
            for(int i = 1; i < sublength && curr->next; i++) curr = curr->next;
            //处理第一个区间的终止位置
            ListNode* head2 = curr->next;
            curr->next = nullptr;
            curr = head2;
            //找第二个区间的终止位置
            //注意 curr && curr->next 判断条件为了对空指针解引用
            for(int i = 1; i < sublength && curr && curr->next; i++) curr = curr->next;
            //处理第二个区间的终止位置（是遍历到了指定的划分单位长度还是遍历到了链表末尾）
            //如果是遍历到了指定的划分单位长度，就处理第二个区间的终止位置
            ListNode* next = nullptr;
            if(curr) next = curr->next, curr->next = nullptr, curr = next;
            //将处理完的两个区间进行合并
            ListNode* merged = merge(head1, head2);
            //移动 prev 到合并后的区间末尾准备下一次的区间划分
            prev->next = merged;
            while(prev->next) prev = prev->next;
        }
    }
    return dummy->next;
}
//注意与链表D:\DataStructure\MyClass\MyLinklist\Code\win3_add leftshift.cpp 中的mergeTwoLinklist进行区分
//其中是传引用，合并则需要 new 每一个节点
//这里是传值，临时变量，直接连起来即可
ListNode* merge(ListNode* head1, ListNode* head2){
    ListNode* pa = head1;
    ListNode* pb = head2;
    ListNode* pc = new ListNode(0);//用于保存合并完链表的头节点
    ListNode* res = pc;//保存头节点的起始位置（pc合并过程中会移动）
    while(pa && pb){
        if(pa->val <= pb->val) pc->next = pa, pa = pa->next;
        else pc->next = pb, pb = pb->next;
        pc = pc->next;
    }
    pc->next = pa == nullptr ? pb : pa;
    return res->next;
}