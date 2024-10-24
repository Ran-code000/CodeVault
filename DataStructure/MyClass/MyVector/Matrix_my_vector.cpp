#include <iostream>
#include <cstring>
using namespace std;
class MyVector {
private:
    int* data;
    int ca;                                                                  
    int sz;                                                                                                                                                                                                               
public:
    MyVector() : data(nullptr), ca(0), sz(0) {}
    ~MyVector() { delete[] data;}
    MyVector(const MyVector& ot) : data(nullptr), ca(ot.ca), sz(ot.sz){                                                                                   
        data = new int[ca];
        memcpy(data, ot.data, sizeof(int) * sz);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    void push_back(const int& value);                                                                                                                                                                                                                                                                                                
    int size() const {return sz;}                                 
    const int& at(int index) const {
        if(index >= 0 && index < sz) return data[index];                                                                                                                   
        else throw out_of_range("Index is out of range");
    }
};
void MyVector::push_back(const int& value) {
    if (sz >= ca) {
        cout << "capacity increase:" << ca;                                                                                       
        if (ca == 0) ca = 1;
        else ca *= 2;
        cout << "->" << ca << endl;
        int* new_data = new int[ca];
        //for (int i = 0; i < sz; ++i) new_data[i] = data[i];
        if(data) memcpy(new_data, data, sizeof(int) * sz);
        //加一句 if(data)，为了防止内存检查出错：
        //runtime error: null pointer passed as argument 2, which is declared to never be null
        delete[] data;
        data = new_data;
    }
    data [sz++] = value;
}
int main(){
    MyVector vec;
    for (int i = 0; i < 17; i++) vec.push_back(i);
    std::cout <<  "size: " << vec.size() << std::endl;
    cout << "vec:\n";
    for (int i = 0; i < vec.size(); ++i) std::cout << vec.at(i) << " ";
    std::cout << std::endl;
    cout << "vecCopy = vec, vec:\n";
    MyVector vecCopy = vec;
    for (int i = 0; i < vec.size(); ++i) std::cout << vecCopy.at(i) << " ";
    std::cout << std::endl;
    cout << "vecCopy.push_back(17)\n";
    vecCopy.push_back(17);
    return 0;
}