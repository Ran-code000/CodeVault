#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
template<typename T>
class MyDeque {
public:
    MyDeque() = default;
    bool empty() const { return container.empty();}
    size_t size() const { return container.size();}
    T& front() {
        if (empty()) throw out_of_range("Deque is empty");
        return container.front();
    }
    const T& front() const {
        if (empty()) throw out_of_range("Deque is empty");
        return container.front();
    }
    T& back() {
        if (empty()) throw out_of_range("Deque is empty");
        return container.back();
    }
    const T& back() const {
        if (empty()) throw out_of_range("Deque is empty");
        return container.back();
    }
    void push_front(const T& value) { container.insert(container.begin(), value);}
    void push_back(const T& value) { container.push_back(value);}
    void pop_front() {
        if (empty()) throw out_of_range("Deque is empty");
        container.erase(container.begin());
    }
    void pop_back() {
        if (empty()) throw out_of_range("Deque is empty");
        container.pop_back();
    }
private:
    vector<T> container; // 使用 vector 作为底层容器
};

int main() {
    MyDeque<int> dq;
    for(int i = 0 ; i < 5; i++) dq.push_back(i);
    cout << "{0, 1, 2, 3, 4}" << endl;
    cout << "Front element: " << dq.front() << endl;
    cout << "Back element: " << dq.back() << endl;
    cout << "Deque size: " << dq.size() << endl;

    dq.pop_front();
    cout << "Front element after pop_front: " << dq.front() << endl;
    cout << "Deque size after pop_front: " << dq.size() << endl;

    dq.pop_back();
    cout << "Back element after pop_back: " << dq.back() << endl;
    cout << "Deque size after pop_back: " << dq.size() << endl;

    return 0;
}
