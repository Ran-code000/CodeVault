#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<typename T>
class Queue{
public:
    Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator= (Queue<T>& other);
    ~Queue();
    bool empty() const;
    size_t size() const;
    T front() const;
    T back() const;
    void push(T val);
    void pop();
    void swap(Queue<T>& other);
    void clear();
    //friend void show(Queue<T> other);
private:
    struct Node{
        T val;
        Node* next;
        //Node(T val, Node* p = nullptr) : val(val), next(p){} //不正确（在第 157 行的测试中）
        //因为初始化列表是因为调用的默认拷贝构造函数（不是默认构造函数）所以只算最开始构造Job对象时的一次
        //输出[5,5][9,9]
        Node(T val, Node* p = nullptr){
            //进行构造函数内部时默认构造一个this->val对象（第二次调用默认构造函数）
            //然后调用默认赋值构造函数（这个跟默认构造函数无关）
            //text3 输出[10,5][18,9]
            this->val = val;
            next = p;
        }
    };
    Node* head;
    Node* tail;
    size_t sz;
};
template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), sz(0){}
template<typename T>
Queue<T>::Queue(const Queue<T>& other) : head(nullptr), tail(nullptr), sz(0) {
    for(Node* curr = other.head; curr != nullptr; curr = curr->next) push(curr->val);
}
template<typename T>
Queue<T>& Queue<T>::operator= (Queue<T>& other){
    if(this == &other) return *this;
    else{
        clear();
        for(Node* curr = other.head; curr != nullptr; curr = curr->next) push(curr->val);
        return *this;
    }
}
template<typename T>
Queue<T>::~Queue(){clear();}
template<typename T>
bool Queue<T>::empty() const{ return sz == 0;}
template<typename T>
size_t Queue<T>::size() const{ return sz;}
template<typename T>
T Queue<T>::front() const{ if(head) return head->val; else return (T)0;}
template<typename T>
T Queue<T>::back() const{ if(tail) return tail->val; else return (T)0;}
template<typename T>
void Queue<T>::push(T val){
    Node* newnode = new Node(val);
    if(empty()) head = tail = newnode;
    else tail->next = newnode, tail = newnode;
    sz++;
}
template<typename T>
void Queue<T>::pop(){
    if(empty()) return;
    else if(size() == 1) delete head, head = tail = nullptr;
    else{
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    sz--;
}
template<typename T>
void Queue<T>::swap(Queue<T>& other){
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(sz, other.sz);
}
template<typename T>
void Queue<T>::clear(){ while(!empty()) pop();}

// void show(Queue<T> other){
//     cout << "My_Queue:";
//     //while(curr) {cout << curr->val << "->"; curr = curr->next;} //错误写法
//     while(other.head){ cout << front() << "->"; other.pop();}
//     cout << "nullptr\n";
// }

//测试函数
class Job {
    public:
        explicit Job(int pri = 0) {
            id = number++;
            priority = pri;
        }
        string toString() {
            stringstream ss;
            ss << "[" << id << ":" << priority << "]";
            return ss.str();
        }
    private:
        static int number;
        int id;
        int priority;
};
int Job::number = 0;

template<typename T>
void show(Queue<T> other){
    cout << "My_Queue:";
    //while(curr) {cout << curr->val << "->"; curr = curr->next;} //错误写法
    while(!other.empty()){ cout << other.front() << "->"; other.pop();}
    cout << "nullptr\n";
}

int main() {
    // test case 1: int..
    cout << "--------------------------------------------------------------------------------\n";
    cout << "test case 1: int..\n";
    Queue<int> que;
    int m, n;
    cout << "Input(number_length, delete_number_length):\n";
    cin >> m >> n;
    for (int i = 0; i < m; i++) que.push(i + 0.01);
    show(que);
    Queue<int> quee(que), queee;
    cout << "quee(que):\n";
    show(quee);
    cout << "queee = quee:\n";
    queee = quee;
    show(queee);
    for (int i = 0; i < n; i++) que.pop();
    if (!que.empty()) {
        cout << "front:" << que.front() << endl;
        cout << "back:" << que.back() << endl;
    }
    cout << "The size is: " << que.size() << endl;
    if (que.empty()) cout << "The queue is empty!" << endl;
    else cout << "The queue is NOT empty!" << endl;

    // test case 2: double..
    cout << "--------------------------------------------------------------------------------\n";
    cout << "test case 2: double\n";
    Queue<double> que1;
    cout << "Input(number_length, delete_number_length):\n";
    cin >> m >> n;
    for (int i = 0; i < m; i++) que1.push(i + 0.01);
    show(que1);
    for (int i = 0; i < n; i++) que1.pop();
    if (!que1.empty()) {
        cout << "que1.front():" << que1.front() << endl;
        cout << "que1.back():" << que1.back() << endl;
    }
    cout << "The size is: " << que1.size() << endl;
    if (que1.empty()) cout << "The queue is empty!" << endl;
    else cout << "The queue is NOT empty!" << endl;

    // test case 3: user defined class..
    cout << "--------------------------------------------------------------------------------\n";
    cout << "test case 3: user defined class\n";
    Queue<Job> que2;
    cout << "Input(number_length, delete_number_length):\n";
    cin >> m >> n;
    for (int i = 0; i < m; i++) que2.push(Job(i));
    //show(que2);
    for (int i = 0; i < n; i++) que2.pop();
    if (!que2.empty()) {
        cout << que2.front().toString() << endl;
        cout << que2.back().toString() << endl;
    }
    cout << "The size is: " << que2.size() << endl;
    if (que2.empty()) cout << "The queue is empty!" << endl;
    else cout << "The queue is NOT empty!" << endl;

    // test case 4: swap function..
    cout << "--------------------------------------------------------------------------------\n";
    cout << "test case 4: swap function..\n";
    Queue<int> que3, que4;
    for (int i = 0; i < m; i++) que3.push(i);
    for (int i = 0; i < n; i++) que4.push(m - i);
    cout << "Before Swap...." << endl;
    show(que3), show(que4);
    cout << "After Swap...." << endl;
    que3.swap(que4);
    show(que3), show(que4);
    return 0;
}

