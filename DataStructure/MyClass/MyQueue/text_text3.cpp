#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<typename T>
class Queue {
public:
    Queue();
    Queue(const Queue<T>& other);
    ~Queue();
    bool IsEmpty() const;
    int getSize() const;
    T getFront() const;
    T getBack() const;
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
        //因为初始化列表是因为调用的默认拷贝/复制构造函数（不是默认构造函数）所以只算最开始构造Job对象时的一次
        //输出[5,5][9,9]
        Node(T val, Node* p = nullptr){
            //进行构造函数内部时默认构造一个this->val对象（第二次调用默认构造函数）
            //然后调用默认赋值构造函数（这个跟默认构造函数无关）
            //text3 输出[10,5][18,9]
            cout << "Before-----this->val[id, priority]" << this->val.toString() << endl;
            this->val = val;
            cout << "After------this->val[id, priority]" << this->val.toString() << endl;
            next = p;
        }
    };
    Node* front_node;
    Node* back_node;
    int size;
};
template<typename T>
Queue<T>::Queue(){ front_node = back_node = nullptr; size = 0;}
template<typename T>
Queue<T>::Queue(const Queue<T>& other){
    if(this == &other) return;
    front_node = back_node = nullptr;
    size = 0;
    Node* p = other.front_node;
    while(p){
        push(p->val);
        p = p->next;
    }
}
template<typename T>
Queue<T>::~Queue(){clear();}
template<typename T>
bool Queue<T>::IsEmpty() const{ return size == 0;}
template<typename T>
int Queue<T>::getSize() const{ return size;}
template<typename T>
T Queue<T>::getFront() const{ if(front_node) return front_node->val; else return (T)0;}
template<typename T>
T Queue<T>::getBack() const{ return back_node->val;}
template<typename T>
void Queue<T>::push(T val){
    Node* newnode = new Node(val);
    if(IsEmpty()) front_node = back_node = newnode;
    else back_node->next = newnode, back_node = newnode;
    size++;
}
template<typename T>
void Queue<T>::pop(){
    if(IsEmpty()) return;
    else if(size == 1) {delete front_node; front_node = back_node = nullptr;}
    else{
        Node* temp = front_node;
        front_node = front_node->next;
        delete temp;
    }
    size--;
}
template<typename T>
void Queue<T>::swap(Queue<T>& other){
    std::swap(front_node, other.front_node);
    std::swap(back_node, other.back_node);
    std::swap(size, other.size);
}
template<typename T>
void Queue<T>::clear(){ while(!IsEmpty()) pop();}

// void show(Queue<T> other){
//     cout << "My_Queue:";
//     //while(curr) {cout << curr->val << "->"; curr = curr->next;} //错误写法
//     while(other.front_node){ cout << getFront() << "->"; other.pop();}
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
    while(!other.IsEmpty()){ cout << other.getFront() << "->"; other.pop();}
    cout << "nullptr\n";
}

int main() {
    int n, m;
    // test case 3: user defined class..
    cout << "--------------------------------------------------------------------------------\n";
    cout << "test case 3: user defined class\n";
    Queue<Job> que2;
    cin >> m >> n; //测试数据10 5；10 20；10 2；
    for (int i = 0; i < m; i++) que2.push(Job(i));
    //show(que2);
    for (int i = 0; i < n; i++) que2.pop();
    if (!que2.IsEmpty()) {
        cout << que2.getFront().toString() << endl;
        cout << que2.getBack().toString() << endl;
    }
    cout << "The size is: " << que2.getSize() << endl;
    if (que2.IsEmpty()) cout << "The queue is empty!" << endl;
    else cout << "The queue is NOT empty!" << endl;
    return 0;
}

