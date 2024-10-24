//实现单链表的插入，删除，反转，求长，判空，寻数，拷贝，清空，打印（增加了重载 << 操作符来实现），升序合并两条有序（升/降）链表， 重载了 + 操作符提供接口（由派生类实现）
//实现了两个派生链表（UpLinklist and DownLinklist）增加功能按升/降序插入链表，重载了加法符号实现链表的合并
//定义基类链表中增加了自定义迭代器（重载了* and ++(前置和后置) and == and != 操作符），从而在定义的基类链表中可以实现 begin() and end()迭代器
#include <iostream>
#include <iomanip>
using namespace std;
//基类定义
struct Listnode{
    int val;
    Listnode* next;
    Listnode(int val, Listnode* p = nullptr) : val(val), next(p){}
};
class Linklist{
protected:
    bool type;
    Listnode* head;
public:
    Linklist(Listnode* p = nullptr, bool type = false) : head(p), type(type){}
    //Linklist(const Linklist& other) : head(other.head){} 错误写法
    Linklist(const Linklist& other);
    Linklist& operator= (const Linklist& other);
    ~Linklist();
    void InsertAtHead(int val);
    void InsertAtEnd(int val);
    void InsertAtPosition(int val, int pos);
    virtual void InsertToUpOrDown(int val);
    void removeAtHead();
    void removeAtEnd();
    void removeAtPosition(int pos);
    void removeAll();
    void removeTheValue(int val);
    void reverseAtRange(int l, int r);
    void reverseAll();
    Listnode* find_the_first(int val);
    int getlength();
    bool IsEmpty();
    void clear();
    void copy(const Linklist& other);
    void display();
    bool getType();
    virtual Linklist* operator+ (Linklist& other);
    friend ostream& operator << (ostream& os, Linklist& a);
    friend Linklist* mergeLinklist(Linklist& a, Linklist& b);

    class iterator{
    private:
        Listnode* curr;
    public: 
        iterator(Listnode* p = nullptr) : curr(p){} 
        int& operator* (){ return curr->val;}
        iterator& operator++ (){
            curr = curr->next;
            return *this;
        }
        iterator operator++ (int){
            iterator temp = *this;
            curr = curr->next;
            return temp;
        }
        bool operator== (const iterator& a){return curr = a.curr;}
        bool operator!= (const iterator& a){return curr != a.curr;}
    };
    iterator begin(){return iterator(head);}
    iterator end(){return iterator(nullptr);}
};
//派生类定义
class UpLinklist : public Linklist{
public:
    UpLinklist() : Linklist(nullptr, true){}
    UpLinklist(const UpLinklist& other) : Linklist(other){}
    UpLinklist& operator= (const UpLinklist& other);
    Linklist* operator+ (Linklist& other);
    void InsertToUpOrDown(int val);
};
class DownLinklist : public Linklist{
public:
    DownLinklist() : Linklist(nullptr){}
    DownLinklist(const DownLinklist& other) : Linklist(other){}
    DownLinklist& operator= (const DownLinklist& other);
    Linklist* operator+ (Linklist& other);
    void InsertToUpOrDown(int val);
    
};
//基类功能实现
Linklist::Linklist(const Linklist& other) : head(nullptr){copy(other);}
Linklist& Linklist::operator= (const Linklist& other){
    if(this == &other) return *this;
    else{
        clear();
        copy(other);
        return *this;
    }
}
Linklist::~Linklist(){clear();}
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
    if(pos > getlength()){throw out_of_range("Out of range!!!"); return;}
    Listnode* newnode = new Listnode(val);
    if(pos == 0){InsertAtHead(val); return;}
    else{
        Listnode* prev;
        Listnode* curr = head;
        int id = 0;
        while(curr && id < pos) prev = curr, curr = curr->next, id++;
        Listnode* newnode = new Listnode(val);
        newnode->next = curr;
        if(prev) prev->next = newnode;
        else head = newnode;//when Linklist_length == 1 and pos == 1 
    }
}
void Linklist::removeAtHead(){
    if(IsEmpty()) return;
    else{
        Listnode* curr = head;
        head = head->next;
        delete curr;
    }
}
void Linklist::removeAtEnd(){
    if(IsEmpty()) return;
    else{
        Listnode* curr = head;
        Listnode* prev = nullptr;
        while(curr->next) prev = curr, curr = curr->next;
        if(prev) prev->next = nullptr, delete curr;
        else delete curr, head = nullptr;
    }
}
void Linklist::removeAtPosition(int pos){
    if(pos > getlength()) {throw out_of_range("Out of range!!!"); return;}
    if(IsEmpty()) return;
    else{
        Listnode* prev = nullptr;
        Listnode* curr = head;
        int id = 0;
        while(curr && id < pos) prev = curr, curr = curr->next, id++;
        if(prev) prev->next = curr->next, delete curr;
        else delete curr, head = nullptr;
    }
}
void Linklist::removeAll(){
    if(IsEmpty()) return;
    else clear();
}
void Linklist::removeTheValue(int val){
    if(IsEmpty()) return;
    else{
        Listnode* curr = head;
        Listnode* prev = nullptr;
        while(curr && curr->val != val) prev = curr, curr = curr->next;
        if(!curr) {throw("Can't find the value"); return;}
        if(prev) prev->next = curr->next, delete curr;
        else delete curr, head = nullptr;
    }
}
void Linklist::reverseAtRange(int l, int r){
    if(getlength() <= 1 || r <= l || l >= getlength()) return;
    Listnode* dum;
    Listnode* p;
    Listnode* q;
    if(l == 0) dum->next = head, p = dum->next, q = p->next;
    else{
        int id = 0;
        while(p && id < l) dum = p, p = p->next, id++;
        q = p->next;
        while(p && q && id < r){
            p->next = q->next;
            q->next = dum->next;
            dum->next = q;
            q = p->next;
            id++;
        }
    } 
}
void Linklist::reverseAll(){
    type = !type;
    if(getlength() <= 1) return;
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
}
Listnode* Linklist::find_the_first(int val){
    if(IsEmpty()) return nullptr;
    else{
        Listnode* curr = head;
        while(curr && curr->val != val) curr = curr->next;
        if(!curr){throw("Can't find the value"); return nullptr;}
        else return curr;
    }    
}
int Linklist::getlength(){
    Listnode* curr = head;
    int len;
    while(curr) curr = curr->next, len++;
    return len;
}
bool Linklist::IsEmpty(){return head == nullptr;}
void Linklist::clear(){
    // Listnode* curr = head;
    // Listnode* prev = nullptr;
    // while(curr) prev = curr, curr = curr->next, delete prev;
    while(head) removeAtEnd();
}
void Linklist::copy(const Linklist& other){for(Listnode* curr = other.head; curr != nullptr; curr = curr->next) InsertAtEnd(curr->val);}
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
bool Linklist::getType(){return type;}
ostream& operator << (ostream& os, Linklist& a){
    if(a.IsEmpty()) os << "nullptr";
    else{
        Listnode* curr = a.head;
        while(curr) os << curr->val << "->", curr = curr->next;
        os << "nullptr" << endl;
        int i = 0;
        curr = a.head;
        while(curr){
            int t = 0;
            int temp = curr->val;
            while(temp){
                temp /= 10;
                t++;
            }
            os << left << setw(t) << i << "  ";
            i++;
            curr = curr->next;
        }
        os << "\n\n";
    }
    return os;
}
Linklist* mergeLinklist(Linklist& a, Linklist& b){
    if(!a.type) a.reverseAll();
    if(!b.type) b.reverseAll();
    Listnode* pa = a.head;
    Listnode* pb = b.head;
    Listnode* pc;
    Listnode* res = pc;
    while(pa && pb){
        if(pa->val <= pb->val) {Listnode* newnode = new Listnode(pa->val); pc->next = newnode; pa = pa->next;}
        else {Listnode* newnode = new Listnode(pb->val); pc->next = newnode; pb = pb->next;}
        pc = pc->next;
    }
    while(pa) {Listnode* newnode = new Listnode(pa->val); pc->next = newnode, pa = pa->next, pc = pc->next;}
    while(pb) {Listnode* newnode = new Listnode(pb->val); pc->next = newnode, pb = pb->next, pc = pc->next;}
    if(a.type) a.reverseAll();
    if(b.type) b.reverseAll();
    Linklist* mergedLinklist = new Linklist(res->next, true);
    return mergedLinklist;
}
//派生类功能实现
UpLinklist& UpLinklist::operator= (const UpLinklist& other){
    if(this == &other) return *this;
    else{Linklist::operator= (other); return *this;}
}
void UpLinklist::InsertToUpOrDown(int val){
    Listnode* newnode = new Listnode(val);
    if(IsEmpty()) head = newnode;
    Listnode* curr = head;
    Listnode* prev = nullptr;
    while(curr && curr->val < val) prev = curr, curr = curr->next;
    newnode->next = curr;
    if(prev) prev->next = newnode;
    //else : when val < head->val; now prev == 0;
}
Linklist* UpLinklist::operator+ (Linklist& other){return mergeLinklist(*this, other);}
DownLinklist& DownLinklist::operator= (const DownLinklist& other){
    if(this == &other) return *this;
    else{Linklist::operator= (other); return *this;}
}
void DownLinklist::InsertToUpOrDown(int val){
    Listnode* newnode = new Listnode(val);
    if(IsEmpty()) return;
    Listnode* curr = head;
    Listnode* prev = nullptr;
    while(curr && curr->val > val) prev = curr, curr = curr->next;
    newnode->next = curr;
    if(prev) prev->next = newnode;
    //else : when val < head->val; now prev == 0;
}
Linklist* DownLinklist::operator+ (Linklist& other){return mergeLinklist(*this, other);}
//text function
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
    cout << dl + dll;
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
