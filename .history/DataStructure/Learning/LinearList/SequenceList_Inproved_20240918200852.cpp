#include <array>
#include <stdexcept>
#include <iostream>
using namespace std;
class SqList {
    static const int max_size = 1024;  
    array<int, max_size> data;    // 使用array来管理数组
    size_t length;                     
public:
    SqList();
    SqList(int a[], size_t n);
    SqList(const SqList &sq);  
    size_t size() const; 
    bool empty() const; 
    void clear();
    int &operator[](size_t i);
    int &back();
    void insert(size_t i, int e);
    void erase(size_t i); 
    void push_back(int e);
    void push_front(int e);
    int pop_back();
    int pop_front();
    void print() const;
};
SqList::SqList() : length(0){}
SqList::SqList(int a[], size_t n) : length(n){
    if(n > max_size) throw out_of_range("n is beyond the maxsize!");
    for(size_t i = 0; i < length; i++) data[i] = a[i];
}
SqList::SqList(const SqList &sq) : length(sq.length){
    for(size_t i = 0; i < sq.length; i++) data[i] = sq.data[i];
} 
size_t SqList::size() const{return length;} 
bool SqList::empty() const{return length == 0;} 
void SqList::clear() {length = 0;}
int& SqList::operator[](size_t i){
    if(i >= length) throw out_of_range("Index out of range");
    return data[i];
}
int& SqList::back(){
    if(empty()) throw out_of_range("List is empty");
    return data[length - 1];
}
void SqList::insert(size_t i, int e){
    if (length >= max_size) throw out_of_range("List is full");
    if (i > length) throw out_of_range("Index out of range");
    for(size_t k = length; k > i; k--) data[k] = data[k - 1];
    data[i] = e;
    length++;
}
void SqList::erase(size_t i){
    if(empty()) throw out_of_range("List is empty");
    if (i >= length) throw out_of_range("Index out of range");
    for(size_t k = i; k < length; k++) data[k]=  data[k + 1];
    length--;
}
void SqList::push_back(int e){ 
    if (length >= max_size) throw out_of_range("List is full");
    data[length++] = e; 
}
void SqList::push_front(int e){
    if (length >= max_size) throw out_of_range("List is full");
    for(size_t i = length; i > 0; i--) data[i] = data[i - 1];
    data[0] = e;
    length++;
}
int SqList::pop_back(){
    if(empty()) throw out_of_range("List is empty");
    return data[--length];
}
int SqList::pop_front(){
    if(empty()) throw out_of_range("List is empty");
    int temp = data[0];
    for(size_t i = 0; i < length; i++) data[i] = data[i + 1];
    return temp;
}
void SqList::print() const{ for(size_t i = 0; i < length; i++) cout << data[i];}
