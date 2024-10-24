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
// 奇数长度:slow 指向中间节点
// 偶数长度:slow 指向中间两个节点的后一个节点
//法三：
// while(fast && fast->next){
//     fast = fast->next->next;
//     if(fast == nullptr) break;
//     slow = slow->next;
// }
// 奇数长度:slow 指向中间节点
// 偶数长度:slow 指向中间两个节点的前一个节点
