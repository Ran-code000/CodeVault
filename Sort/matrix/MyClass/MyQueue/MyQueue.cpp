#include <iostream>
#include <deque>
using namespace std;
template<typename T>
class MyQueue {
public:
    MyQueue() = default;
    bool empty() const { return container.empty();}
    size_t size() const { return container.size();}
    T& front() { return container.front();}
    const T& front() const { return container.front();}
    T& back() { return container.back();}
    const T& back() const { return container.back();}
    void push(const T& value) { container.push_back(value);}
    void pop() { container.pop_front();}
private:
    deque<T> container; // 使用 deque 作为底层容器
};
int main(){
    MyQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    cout << "{10, 20, 30}" << endl;

    cout << "Front element: " << q.front() << endl;
    cout << "Back element: " << q.back() << endl;
    cout << "Queue size: " << q.size() << endl;

    q.pop();
    cout << "Front element after pop: " << q.front() << endl;
    cout << "Queue size after pop: " << q.size() << endl;

    return 0;
}
