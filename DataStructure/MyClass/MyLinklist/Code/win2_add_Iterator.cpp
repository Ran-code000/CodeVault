#include <iostream>
#include <iomanip>
using namespace std;
struct Listnode{
    int val;
    Listnode* next;
    Listnode(int val = 0, Listnode* p = nullptr) : val(val), next(p){}
};
class Linklist{
protected:
    Listnode* head;
    bool type;
public:
    Linklist(Listnode* p = nullptr, bool t = false) : head(p), type(t){}
    ~Linklist();
    Linklist(const Linklist& other);
    Linklist& operator= (const Linklist& other);
    void InsertToUpOrDown(int val);
    void InsertAtHead(int val);
    void InsertAtEnd(int val);
    void InsertAtPosition(int val, int pos);
    void removeAll();
    void removeAtHead();
    void removeAtEnd();
    void removeAtPosition(int pos);
    void removeTheValue(int val);
    Listnode* find_the_first(int val);
    void reverseAll();
    void reverseAtRange(int start, int end);
    int getlength();
    bool IsEmpty();
    void display();
    void clear();
    bool getType(){return type;}
    friend Linklist* mergeLinklist(Linklist& a, Linklist& b);

    class iterator{
    private:
        Listnode* curr;
    public:
        iterator(Listnode* p) : curr(p){}
        int& operator* (){ return curr->val;}
        iterator& operator++(){
            curr = curr->next;
            return *this;
        }
        iterator operator++ (int){
            iterator temp = *this;
            curr = curr->next;
            return temp;
        }
        bool operator== (const iterator& other){
            return curr == other.curr;
        }
        bool operator!= (const iterator& other){
            return curr != other.curr;
        }
    };
    iterator begin(){ return iterator(head);}
    iterator end(){ return iterator(nullptr);}
};
class UpLinklist : virtual public Linklist{
public:
    UpLinklist() : Linklist(nullptr, true){}
    UpLinklist(const UpLinklist& other) : Linklist(other){}
    UpLinklist& operator= (const UpLinklist& other);
    void InsertToUpOrDown(int val);
    Linklist* operator+ (Linklist& other);
    void display();
};
class DownLinklist : virtual public Linklist{
public:
    DownLinklist() : Linklist(nullptr, false){}
    DownLinklist(const DownLinklist& other) : Linklist(other){}
    DownLinklist& operator= (const DownLinklist& other);
    void InsertToUpOrDown(int val);
    Linklist*  operator+ (Linklist& other);
    void display();
};
Linklist::Linklist(const Linklist& other) : head(nullptr) {
    type = other.type;
    for(Listnode* curr = other.head; curr != nullptr; curr = curr->next) InsertAtEnd(curr->val);
}
Linklist& Linklist::operator= (const Linklist& other){
    if(this == &other) return *this;
    else{
        clear();
        type = other.type;
        for(Listnode* curr = other.head; curr != nullptr; curr = curr->next) InsertAtEnd(curr->val);
    }
    return *this;
}
Linklist::~Linklist(){ clear();}
void Linklist::InsertAtHead(int val){
    Listnode* newnode = new Listnode(val, head);
    head = newnode;
}
void Linklist::InsertAtEnd(int val){
    Listnode* newnode = new Listnode(val);
    if(IsEmpty()) head = newnode;
    else{
        Listnode* curr = head;
        while(curr->next) curr = curr->next;
        curr->next = newnode;
    }
}
void Linklist::InsertAtPosition(int val, int pos){
    if(pos > getlength()) return;
    Listnode* newnode = new Listnode(val);
    if(pos == 0) {InsertAtHead(val); return;}
    else{
        Listnode* prev = nullptr;
        Listnode* curr = head;
        int ind = 0;
        while(curr && ind < pos){prev = curr; curr = curr->next; ind++;}
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else head = newnode;
    }
}
void Linklist::removeAtHead(){
    Listnode* curr = head;
    if(IsEmpty()) return;
    else head = head->next, delete curr;
}
void Linklist::removeAtEnd(){
    Listnode* curr = head;
    if(IsEmpty()) return;
    else if(getlength() == 1){delete curr; head = nullptr; return;}
    else{
        Listnode* prev = nullptr;
        while(curr->next) prev = curr, curr = curr->next;
        delete curr;
        prev->next = nullptr;
    }
}
void Linklist::removeAtPosition(int pos){
    if(IsEmpty() || pos > getlength()) return;
    else{
        if(pos == 0) removeAtHead();
        else{
            Listnode* curr = head;
            Listnode* prev = nullptr;
            int ind = 0;
            while(curr && ind < pos) prev = curr, curr = curr->next, ind++;
            if(prev) prev->next = curr->next;
            delete curr;
        }
    }
}
void Linklist::removeTheValue(int val){
    if(IsEmpty()) return;
    else if(val == head->val) {head == nullptr; return;}
    else{
        Listnode* curr = head;
        Listnode* prev = nullptr;
        while(curr && curr->val != val) prev = curr, curr = curr->next;
        if(!curr) return;
        else prev->next = curr->next, delete curr;
    }
}
int Linklist::getlength(){
    if(IsEmpty()) return 0;
    else{
        Listnode* curr = head;
        int len = 0;
        while(curr) curr = curr->next, len++;
        return len;
    }
}
void Linklist::display(){
    if(IsEmpty()) cout << "nullptr";
    else{
        Listnode* curr = head;
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
bool Linklist::IsEmpty(){ return head == nullptr;}
Listnode* Linklist::find_the_first(int val){
    if(IsEmpty()) return nullptr;
    else{
        Listnode* curr = head;
        while(curr && curr->val != val) curr = curr->next;
        if(!curr) return nullptr;
        else return curr;
    }
}
void Linklist::removeAll(){
    if(head == nullptr) return;
    else clear();
}
void Linklist::reverseAll(){
    if(IsEmpty() || head->next == nullptr) return;
    else{
        Listnode* dum = new Listnode(0, head);
        Listnode* p = dum->next;
        Listnode* q = p->next;
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
void Linklist::reverseAtRange(int beg, int end){
    if(IsEmpty()) return;
    else{
        Listnode* prev;
        Listnode* p = head;
        Listnode* q;
        int ind = 0;
        if(beg == 0) prev = new Listnode(0, head), p = prev->next;
        else while(p && ind < beg) prev = p, p = p->next, ind++;
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
void Linklist::clear(){ while(head) removeAtEnd();}
void DownLinklist::InsertToUpOrDown(int val){
    // Listnode* newnode = new Listnode(val);
    // if(IsEmpty()) head = newnode;
    // else{
    //     Listnode* curr = head;
    //     Listnode* prev = nullptr;
    //     while(curr && val < curr->val) prev = curr, curr = curr->next;
    //     newnode->next = curr;
    //     if(prev) prev->next = newnode;
    //     else newnode->next = head, head = newnode;
    // }
    //写法二
    Listnode* newnode = new Listnode(val);
    if(IsEmpty()) head = newnode;
    else if(val > head->val) newnode->next = head, head = newnode;//特判所有在头节点前插入（）即导致else中prev == nullptr的情况
    //else if(head->next == nullptr && val > head->val) newnode->next = head, head = newnode; 不正确
    else{
        Listnode* curr = head;
        Listnode* prev = nullptr;
        while(curr && curr->val > val) prev = curr, curr = curr->next;
        newnode->next = curr;
        prev->next = newnode;//由于已经特判了prev可能为nullptr的情况，所以这里不用 if(prev) prev->next = newnode;
    }
}
void DownLinklist::display(){
    Linklist::display();
}
void UpLinklist::display(){
    Linklist::display();
}
void UpLinklist::InsertToUpOrDown(int val){
    Listnode* newnode = new Listnode(val);
    if(IsEmpty()) head = newnode;
    else{
        Listnode* curr = head;
        Listnode* prev = nullptr;
        while(curr && val > curr->val) prev = curr, curr = curr->next;
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else newnode->next = head, head = newnode;
    }
    //写法二
    // Listnode* newnode = new Listnode(val);
    // if(IsEmpty()) head = newnode;
    // else if(val < head->val) newnode->next = head, head = newnode;//特判所有在头节点前插入（）即导致else中prev == nullptr的情况
    // //else if(head->next == nullptr && val < head->val) newnode->next = head, head = newnode; 不正确
    // else{
    //     Listnode* curr = head;
    //     Listnode* prev = nullptr;
    //     while(curr && curr->val < val) prev = curr, curr = curr->next;
    //     newnode->next = curr;
    //     prev->next = newnode;//由于已经特判了prev可能为nullptr的情况，所以这里不用 if(prev) prev->next = newnode;
    // }
}
Linklist* mergeLinklist(Linklist& a, Linklist& b){
    int fa = 0, fb = 0;
    cout << a.getType() << " " << b.getType() << endl;
    if (!a.getType()) a.reverseAll(), fa = 1;
    if (!b.getType()) b.reverseAll(), fb = 1;
    a.display();
    b.display();
    Listnode* pa = a.head;
    Listnode* pb = b.head;
    Listnode* pc = new Listnode;
    Listnode* res = pc;
    while(pa && pb){
        //if(pa->val <= pb->val) pc->next = pa, pa = pa->next;
        if(pa->val <= pb->val){
            Listnode* newnode = new Listnode(pa->val);
            pc->next = newnode, pa = pa->next;
        }
        //else if(pa->val > pb->val) pc->next = pb, pb = pb->next;
        else if(pa->val > pb->val){
            Listnode* newnode = new Listnode(pb->val);
            pc->next = newnode, pb = pb->next;
        }
        pc = pc->next;
    }
    //pc->next = pa == nullptr ? pb : pa;
    while(pa){
        Listnode* newnode = new Listnode(pa->val);
        pc->next = newnode, pa = pa->next;
        pc = pc->next;
    }
    while(pb){
        Listnode* newnode = new Listnode(pb->val);
        pc->next = newnode, pb = pb->next;
        pc = pc->next;
    }
    Linklist* mergedList = new Linklist(res->next);
    if(fa) a.reverseAll();
    if(fb) b.reverseAll();
    return mergedList;    
}
UpLinklist& UpLinklist::operator= (const UpLinklist& other){
    if(this == &other) return *this;
    else {Linklist::operator= (other); return *this;}
}
DownLinklist& DownLinklist::operator= (const DownLinklist& other){
    if(this == &other) return *this;
    else {Linklist::operator= (other); return *this;}
}
Linklist* UpLinklist::operator+ (Linklist& other){
    return mergeLinklist(*this, other);
}
Linklist* DownLinklist::operator+ (Linklist& other){
    return mergeLinklist(*this, other);
}
int main(){
    Linklist l, ll;
    cout << "length:" << l.getlength() << endl;
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
    cout << "length: " << l.getlength() << endl;
    l.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "InsertAtPos: (99, 0)(999, 10)(9999, 37)" << endl;
    l.InsertAtPosition(99, 0);
    l.InsertAtPosition(999, l.getlength());
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
    cout <<  "Linklist lll(l):\n";
    cout << "l:\n";
    l.display();
    Linklist lll(ll);
    cout << "lll:\n";
    lll.display();
    cout << "---------------------------------------------------------------------------\n";
    DownLinklist dl, dll;
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
    cout << "mergeLinklist(dl, dll):\n";
    mergeLinklist(dl, dll)->display();
    dl.display();
    dll.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "dl = dl + dll:\n";
    (dl + dll)->display();
    cout << "---------------------------------------------------------------------------\n";
    UpLinklist ul, ull;
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
    cout << "mergeLinklist(ul, ull):\n";
    mergeLinklist(ul, ull)->display();
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
    cout << "\n---------------------------------------------------------------------------\n";
    cout << "display with iterator\n";
    Linklist ls;
    for(int i = 0; i < 5; i++) ls.InsertAtHead(i);
    cout << "4, 3, 2, 1, 0\n";
    for(auto it = ls.begin(); it != ls.end(); it++) cout << *it << " ";
    cout << endl;
    return 0;
}