#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;
template <typename T>
class MyVector {
public:
    MyVector();
    MyVector(size_t initialsz);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    ~MyVector();
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void clear();
    void resize(size_t newsz);
    void reserve(size_t newca);
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    class intertor{
    private:
        T* curr;
    public:
        intertor(T* p) : curr(p){}
        T& operator* (){
            return *curr;
        }
        intertor& operator++ (){
            curr++;
            return *this;
        }
        intertor operator++ (int){
            intertor temp = *this;
            curr++;
            return temp;
        }
        intertor& operator-- (){
            if(curr) curr--;
            return *this;
        }
        intertor operator-- (int){
            intertor temp = *this;
            if(curr) curr--;
            return temp;
        }
        bool operator== (const intertor& other){
            return curr == other.curr;
        }
        bool operator!= (const intertor& other){
            return curr != other.curr;
        }
    };
    intertor begin(){
        return intertor(data);
    }
    intertor end(){
        return intertor(data + sz);
    }
private:
    T* data;
    size_t sz;
    size_t ca;
    void reallocate(size_t newca);
};
template <typename T>
MyVector<T>::MyVector() : data(nullptr), sz(0), ca(0) {}
template <typename T>
MyVector<T>::MyVector(size_t initialsz) : data(nullptr), sz(initialsz), ca(initialsz) {
    data = new T[ca];
}
template <typename T>
MyVector<T>::MyVector(const MyVector& other) : data(nullptr), sz(other.sz), ca(other.ca) {
    data = new T[ca];
    //copy(other.data, other.data + sz, data);
    memcpy(data, other.data, sizeof(T) * ca);
}
template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept : data(other.data), sz(other.sz), ca(other.ca) {
    other.data = nullptr;
    other.sz = 0;
    other.ca = 0;
}
template <typename T>
MyVector<T>::~MyVector() { delete[] data;}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) return *this;
    else{
        if(data) delete[] data;
        sz = other.sz;
        ca = other.ca;
        data = new T[ca];
        //copy(other.data, other.data + sz, data);
        memcpy(data, other.data, sizeof(T) * ca);
    }
    return *this;
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if(this == &other) return *this;
    else{
        if(data) delete[] data;
        data = other.data;
        sz = other.sz;
        ca = other.ca;
        other.data = nullptr;
        other.sz = 0;
        other.ca = 0;
    }
    return *this;
}
template <typename T>
T& MyVector<T>::operator[](size_t index) { return data[index];}
template <typename T>
const T& MyVector<T>::operator[](size_t index) const { return data[index];}
template <typename T>
T& MyVector<T>::at(size_t index) {
    if(index >= 0 && index < sz) return data[index];
    else throw out_of_range("Index is out of range");
}
template <typename T>
const T& MyVector<T>::at(size_t index) const {
    if(index >= 0 && index < sz) return data[index];
    else throw out_of_range("Index is out of range");
}
template <typename T>
T& MyVector<T>::front() { return data[0];}
template <typename T>
const T& MyVector<T>::front() const { return data[0];}
template <typename T>
T& MyVector<T>::back() { return data[sz - 1];}
template <typename T>
const T& MyVector<T>::back() const { return data[sz - 1];}
template <typename T>
void MyVector<T>::push_back(const T& value) {
    if(sz >= ca) reallocate(ca > 0 ? ca * 2 : 1);
    data[sz++] = value;
}
template <typename T>
void MyVector<T>::push_back(T&& value) {
    if(sz >= ca) reallocate(ca > 0 ? ca * 2 : 1);
    data[sz++] = move(value);
}
template <typename T>
void MyVector<T>::pop_back() { if(sz > 0) --sz;}
template <typename T>
void MyVector<T>::clear() { sz = 0;}
template <typename T>
void MyVector<T>::resize(size_t newsz) {
    if(newsz > ca) reallocate(newsz);
    else sz = newsz;
}
template <typename T>
void MyVector<T>::reserve(size_t newca) {
    if (newca > ca) reallocate(newca);
}
template <typename T>
size_t MyVector<T>::size() const noexcept { return sz;}
template <typename T>
size_t MyVector<T>::capacity() const noexcept { return ca;}
template <typename T>
bool MyVector<T>::empty() const noexcept { return sz == 0;}
template <typename T>
void MyVector<T>::reallocate(size_t newca) {
    T* new_data = new T[newca];
    //copy(data, data + sz, new_data);
    if(data) memcpy(new_data, data, sizeof(T) * sz);
    //加一句 if(data)，为了防止内存检查出错：
        //runtime error: null pointer passed as argument 2, which is declared to never be null
    delete[] data;
    data = new_data;
    ca = newca;
}
int main(){
    MyVector<int> vec;
    for(int i = 10; i < 20; i++) vec.push_back(i);
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    std::cout << "\nBefore pop_back, size: " << vec.size() << std::endl;
    vec.pop_back();
    std::cout << "After pop_back, size: " << vec.size() << std::endl;
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    cout << endl;
    vec.resize(5);
    std::cout << "After resize(5), size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    cout << endl;
    vec.reserve(10);
    std::cout << "After reserve(10), capacity: " << vec.capacity() << std::endl;
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    cout << endl;
    cout << "-----------------------------------------------------------------\n";
    for(auto it = vec.begin(); it != vec.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
