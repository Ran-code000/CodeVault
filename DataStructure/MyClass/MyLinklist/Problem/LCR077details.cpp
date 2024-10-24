//细节探索：
//法一（不太健壮但针对这个代码也能过，原因见 LCR077details.cpp）
// while(fast != tail){
//     slow = slow->next;
//     fast = fast->next;
//     if(fast != tail) fast = fast->next;
// }
//法二（更加健壮）
// while(fast != tail && fast->next != tail){
//     slow = slow->next;
//     fast = fast->next->next;
// }

// 1. 为什么在 LCR077 的代码中第一个 while (fast && fast->next) 是正确的？
// （1）分割到最小单位： 在归并排序的递归过程中，我们总是会把链表拆到只剩下一个或两个节点，因此，链表长度会被极端缩短。
//     即使使用第二种 while (fast) 方案，由于链表变得非常短，甚至只有1-2个节点的情况下，这两种写法都会有效，因为不会触发越界问题。

// （2）链表末端的特殊处理： 在归并排序中，链表是通过两个指针 head 和 tail 进行划分的，而不是单纯依赖 nullptr 判断（）。
//     虽然在调用 sortList 时传入的 tail 是 nullptr，但是在后续的递归调用中，当链表被逐渐分割时，tail 会在内部变为指向链表中某个具体节点的地址，从而保证每一段链表的处理是独立的。
//     因此，即便在循环2中未严格检查 fast->next，链表也不会访问到空指针，避免了问题的发生。

// 2.奇偶性问题：
//    如果链表长度是 奇数，这种写法仍然能够工作，因为 fast 最终会指向最后一个节点，slow 会指向中间节点。
//    但是如果链表长度是 偶数，fast 会在最后一轮循环中走到链表的末尾，并尝试再走两步，这时可能会产生问题，因为没有提前检查 fast->next 的存在性。

// 3.尽可能使用第二种方法（确保在执行 fast = fast->next; 之前，fast->next 不是 nullptr）
//     此时如果链表长度是 奇数，slow 会指向中间节点。
//         如果链表长度是 偶数，slow 会指向中间靠后的节点（若需要将链表分成两段只需 ListNode* next = slow->next, slow->next = nullptr）
//                              若链表是 1->3->2->4，最后 slow 指向 2





