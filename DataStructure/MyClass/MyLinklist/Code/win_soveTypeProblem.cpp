#include <iostream>
#include <iomanip>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val = 0, ListNode* p = nullptr) : val(val), next(p){}
};
class LinkList{
protected:
    ListNode* head;
    bool type;
public:
    LinkList(ListNode* p = nullptr, bool t = false) : head(p), type(t){}
    ~LinkList();
    LinkList(const LinkList& other);
    LinkList& operator= (const LinkList& other);
    void InsertToUpOrDown(int val);
    void InsertAtHead(int val);
    void InsertAtEnd(int val);
    void InsertAtPosition(int val, int pos);
    void removeAll();
    void removeAtHead();
    void removeAtEnd();
    void removeAtPosition(int pos);
    void removeTheValue(int val);
    ListNode* find(int val);
    void reverseAll();
    void reverseAtRange(int start, int end);
    int getLength();
    bool IsEmpty();
    void display();
    void clear();
    bool getType(){return type;}
    friend LinkList* mergeLinkList(LinkList& a, LinkList& b);
};
class UpLinkList : virtual public LinkList{
public:
    UpLinkList() : LinkList(nullptr, true){}
    UpLinkList(const UpLinkList& other) : LinkList(other){}
    UpLinkList& operator= (const UpLinkList& other);
    void InsertToUpOrDown(int val);
    LinkList* operator+ (LinkList& other);
    void display();
};
class DownLinkList : virtual public LinkList{
public:
    DownLinkList() : LinkList(nullptr, false){}
    DownLinkList(const DownLinkList& other) : LinkList(other){}
    DownLinkList& operator= (const DownLinkList& other);
    void InsertToUpOrDown(int val);
    LinkList*  operator+ (LinkList& other);
    void display();
};
LinkList::LinkList(const LinkList& other) : head(nullptr) {
    // head = nullptr;
    // type = other.type;
    // ListNode* p= other.head;
    // ListNode* curr = head;
    // while(p){
    //     ListNode* newnode = new ListNode(p->val);
    //     if(head == nullptr) head = curr = newnode;
    //     else curr->next = newnode, curr = curr->next;
    //     //法一：InsertAtEnd(p->val);
    //     p = p->next;
    // }
    type = other.type;
    for(ListNode* curr = other.head; curr != nullptr; curr = curr->next) InsertAtEnd(curr->val);
}
LinkList& LinkList::operator= (const LinkList& other){
    // if(this == &other) return *this;
    // else{
    //     clear();
    //     head = nullptr;
    //     type = other.type;
    //     ListNode* p = other.head;
    //     ListNode* curr = head;
    //     while(p){
    //         ListNode* newnode = new ListNode(p->val);
    //         if(head == nullptr) head = curr = newnode;
    //         else curr->next = newnode, curr = curr->next;
    //         p = p->next;
    //     }
    //     return *this;
    // }
    if(this == &other) return *this;
    else{
        clear();
        type = other.type;
        for(ListNode* curr = other.head; curr != nullptr; curr = curr->next) InsertAtEnd(curr->val);
    }
    return *this;
}
LinkList::~LinkList(){ clear();}
void LinkList::InsertAtHead(int val){
    ListNode* newnode = new ListNode(val, head);
    head = newnode;
}
void LinkList::InsertAtEnd(int val){
    ListNode* newnode = new ListNode(val);
    if(IsEmpty()) head = newnode;
    else{
        ListNode* curr = head;
        while(curr->next) curr = curr->next;
        curr->next = newnode;
    }
}
void LinkList::InsertAtPosition(int val, int pos){
    if(pos > getLength()) return;
    ListNode* newnode = new ListNode(val);
    if(pos == 0) {InsertAtHead(val); return;}
    else{
        ListNode* prev = nullptr;
        ListNode* curr = head;
        int ind = 0;
        while(curr && ind < pos){prev = curr; curr = curr->next; ind++;}
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else head = newnode;
    }
}
void LinkList::removeAtHead(){
    ListNode* curr = head;
    if(IsEmpty()) return;
    else head = head->next, delete curr;
}
void LinkList::removeAtEnd(){
    ListNode* curr = head;
    if(IsEmpty()) return;
    else if(getLength() == 1){delete curr; head = nullptr; return;}
    else{
        ListNode* prev = nullptr;
        while(curr->next) prev = curr, curr = curr->next;
        delete curr;
        prev->next = nullptr;
    }
}
void LinkList::removeAtPosition(int pos){
    if(IsEmpty() || pos > getLength()) return;
    else{
        if(pos == 0) removeAtHead();
        else{
            ListNode* curr = head;
            ListNode* prev = nullptr;
            int ind = 0;
            while(curr && ind < pos) prev = curr, curr = curr->next, ind++;
            if(prev) prev->next = curr->next;
            delete curr;
        }
    }
}
void LinkList::removeTheValue(int val){
    if(IsEmpty()) return;
    else if(val == head->val) {head == nullptr; return;}
    else{
        ListNode* curr = head;
        ListNode* prev = nullptr;
        while(curr && curr->val != val) prev = curr, curr = curr->next;
        if(!curr) return;
        else prev->next = curr->next, delete curr;
    }
}
int LinkList::getLength(){
    if(IsEmpty()) return 0;
    else{
        ListNode* curr = head;
        int len = 0;
        while(curr) curr = curr->next, len++;
        return len;
    }
}
void LinkList::display(){
    if(IsEmpty()) cout << "nullptr";
    else{
        ListNode* curr = head;
        while(curr) cout << curr->val << "->", curr = curr->next;
        cout << "nullptr" << endl;
        int i = 0;
        curr = head;
        while(curr){
            int t = 0;
            int temp = curr->val;
            while(temp){
                temp /= 10;
                t++;
            }
            cout << left << setw(t) << i << "  ";
            i++;
            curr = curr->next;
        }
        cout << "\n\n";
    }
}
bool LinkList::IsEmpty(){
    return head == nullptr;
}
ListNode* LinkList::find(int val){
    if(IsEmpty()) return nullptr;
    else{
        ListNode* curr = head;
        while(curr && curr->val != val) curr = curr->next;
        if(!curr) return nullptr;
        else return curr;
    }
}
void LinkList::removeAll(){
    if(head == nullptr) return;
    else clear();
}
void LinkList::reverseAll(){
    if(IsEmpty() || head->next == nullptr) return;
    else{
        ListNode* dum = new ListNode(0, head);
        ListNode* p = dum->next;
        ListNode* q = p->next;
        while(p && q){
            p->next = q->next;
            q->next = dum->next;
            dum->next = q;
            q = p->next;
        }
        if(dum) head = dum->next, delete dum;
        type = !getType();
    }
}
void LinkList::reverseAtRange(int beg, int end){
    if(IsEmpty()) return;
    else{
        ListNode* prev;
        ListNode* p = head;
        ListNode* q;
        int ind = 0;
        if(beg == 0) prev = new ListNode(0, head), p = prev->next;
        else while(p && ind < beg) {prev = p, p = p->next, ind++;}
        if(!p) return; else q = p->next;
        while(p && q && ind < end){
            p->next = q->next;
            q->next = prev->next;
            prev->next = q;
            q = p->next;
            ind++;
        }
    }
}
void LinkList::clear(){
    //法一：while(head){
    //     ListNode* nextnode = head->next;
    //     delete head;
    //     head = nextnode;
    // }
    // ListNode* curr = head;
    //法二：ListNode* prev = nullptr;
    // while(curr) prev = curr, curr = curr->next, delete prev;
    while(head) removeAtEnd();
}
void DownLinkList::InsertToUpOrDown(int val){
    ListNode* newnode = new ListNode(val);
    if(IsEmpty()) head = newnode;
    else{
        ListNode* curr = head;
        ListNode* prev = nullptr;
        while(curr && val < curr->val) prev = curr, curr = curr->next;
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else newnode->next = head, head = newnode;
    }
}
void DownLinkList::display(){
    LinkList::display();
}
void UpLinkList::display(){
    LinkList::display();
}
void UpLinkList::InsertToUpOrDown(int val){
    ListNode* newnode = new ListNode(val);
    if(IsEmpty()) head = newnode;
    else{
        ListNode* curr = head;
        ListNode* prev = nullptr;
        while(curr && val > curr->val) prev = curr, curr = curr->next;
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else newnode->next = head, head = newnode;
    }
}
LinkList* mergeLinkList(LinkList& a, LinkList& b){
    int fa = 0, fb = 0;
    cout << a.getType() << " " << b.getType() << endl;
    if (!a.getType()) a.reverseAll(), fa = 1;
    if (!b.getType()) b.reverseAll(), fb = 1;
    a.display();
    b.display();
    ListNode* pa = a.head;
    ListNode* pb = b.head;
    ListNode* pc = new ListNode;
    ListNode* res = pc;
    while(pa && pb){
        if(pa->val <= pb->val){
            ListNode* newnode = new ListNode(pa->val);
            pc->next = newnode, pa = pa->next;
        }
        else if(pa->val > pb->val){
            ListNode* newnode = new ListNode(pb->val);
            pc->next = newnode, pb = pb->next;
        }
        pc = pc->next;
    }
    //pc->next = pa == nullptr ? pb : pa;
    while(pa){
        ListNode* newnode = new ListNode(pa->val);
        pc->next = newnode, pa = pa->next;
        pc = pc->next;
    }
    while(pb){
        ListNode* newnode = new ListNode(pb->val);
        pc->next = newnode, pb = pb->next;
        pc = pc->next;
    }
    LinkList* mergedList = new LinkList(res->next);
    if(fa) a.reverseAll();
    if(fb) b.reverseAll();
    return mergedList;    
}
UpLinkList& UpLinkList::operator= (const UpLinkList& other){
    if(this == &other) return *this;
    else {LinkList::operator= (other); return *this;}
}
DownLinkList& DownLinkList::operator= (const DownLinkList& other){
    if(this == &other) return *this;
    else {LinkList::operator= (other); return *this;}
}
LinkList* UpLinkList::operator+ (LinkList& other){
    return mergeLinkList(*this, other);
}
LinkList* DownLinkList::operator+ (LinkList& other){
    return mergeLinkList(*this, other);
}
int main(){
    LinkList l, ll;
    cout << "length:" << l.getLength() << endl;
    cout << "---------------------------------------------------------------------------\n";
    cout << "InsertAtHead: 1, 2, 3, 4, 5; InsertAtend : 6, 7, 8, 9" << endl;
    l.InsertAtHead(1);
    l.InsertAtHead(2);
    l.InsertAtHead(3);
    l.InsertAtHead(4);
    l.InsertAtHead(5);
    l.InsertAtEnd(6);
    l.InsertAtEnd(7);
    l.InsertAtEnd(8);
    l.InsertAtEnd(9);
    cout << "length: " << l.getLength() << endl;
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "InsertAtPos: (99, 0)(999, 10)(9999, 37)" << endl;
    l.InsertAtPosition(99, 0);
    l.InsertAtPosition(999, l.getLength());
    l.InsertAtPosition(9999, 37);
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "reverseAll:\n";
    l.reverseAll();
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "removeAtPosition(2):\n";
    l.removeAtPosition(2);
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "reverse 2 ~ 6\n";
    l.reverseAtRange(2, 6);
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "ll = l:\n";
    cout << "l:\n";
    l.display();
    ll = l;
    cout << "ll:\n";
    ll.display();
    cout << "---------------------------------------------------------------------------\n";
    cout <<  "LinkList lll(l):\n";
    cout << "l:\n";
    l.display();
    LinkList lll(ll);
    cout << "lll:\n";
    lll.display();
    cout << "---------------------------------------------------------------------------\n";
    DownLinkList dl, dll;
    cout << "down(dl):\n";
    cout << "InsertToDown(222, 666, 444, 888, 111, 999, 0, 11111):\n";
    dl.InsertToUpOrDown(222);
    dl.InsertToUpOrDown(666);
    dl.InsertToUpOrDown(444);
    dl.InsertToUpOrDown(888);
    dl.InsertToUpOrDown(111);
    dl.InsertToUpOrDown(999);
    dl.InsertToUpOrDown(0);
    dl.InsertToUpOrDown(11111);
    dl.display();
    cout << "down(dll):\n";
    cout << "InsertToDown(9, 8, 7, 11, 13, 223, 0, 333):\n";
    dll.InsertToUpOrDown(9);
    dll.InsertToUpOrDown(8);
    dll.InsertToUpOrDown(7);
    dll.InsertToUpOrDown(11);
    dll.InsertToUpOrDown(13);
    dll.InsertToUpOrDown(223);
    dll.InsertToUpOrDown(0);
    dll.InsertToUpOrDown(333);
    dll.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "mergeLinkList(dl, dll):\n";
    mergeLinkList(dl, dll)->display();
    dl.display();
    dll.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "dl = dl + dll:\n";
    (dl + dll)->display();
    cout << "---------------------------------------------------------------------------\n";
    UpLinkList ul, ull;
    cout << "up(ul):\n";
    cout << "InsertToUp(7, 6, 5, 999, 0, 1000):\n";
    ul.InsertToUpOrDown(7);
    ul.InsertToUpOrDown(6);
    ul.InsertToUpOrDown(5);
    ul.InsertToUpOrDown(999);
    ul.InsertToUpOrDown(0);
    ul.InsertToUpOrDown(1000);
    ul.display();
    cout << "up(ull):\n";
    cout << "InsertToUp(66, 55, 44, 3, 0, 1001):\n";
    ull.InsertToUpOrDown(66);
    ull.InsertToUpOrDown(55);
    ull.InsertToUpOrDown(44);
    ull.InsertToUpOrDown(3);
    ull.InsertToUpOrDown(0);
    ull.InsertToUpOrDown(1001);
    ull.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "mergeLinkList(ul, ull):\n";
    mergeLinkList(ul, ull)->display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "ul = ul + ull:\n";
    (ul + ull)->display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "ul = ul + dl:\n";
    (ul + dl)->display();
    cout << "dl:\n";
    dl.display();
    cout << "dl.type:\n";
    cout << dl.getType();
    return 0;
}