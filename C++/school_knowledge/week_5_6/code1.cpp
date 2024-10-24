#include <iostream>
#include <string>
using namespace std;
class Text{
    string s;
public:
    Text(const char* s) : s(s){

    }
    void print(){
        cout << s << "\n";
    }
};
class A { 
    int m; 
public: 
    A(int x): m(x) { } 
    A(const A&) = delete;// Delete the copy assignment operator 
    A& operator=(const A&) = delete;  
}; 
class B{ 
public: 
    int func() = default;// Error, func is not a special member function. 
    B(int, int) = default;// Error, constructor B(int, int) is not a special member function. 
    B(int = 0) = default;// Error, constructor B(int=0) has a default argument. 
};
int main(){
    Text* str_ptr = new Text("on heap1");
    str_ptr -> print();
    delete str_ptr;
    string *p = new string[4]{
        string(5, 'a'),
        string(5, 'b'),
        string(5, 'c'),
        string(5, 'd')
    };
    delete[] p;

    int *pp = new int[5]{1, 3, 5, 7, 9};
    delete pp;
    
    A a1(1), a2(2), a3(3);
    a1 = a2;// Error, the usage of the copy assignment operator is disabled 
    a3 = A(a2);// Error, the usage of the copy constructor is disabled 
    return 0;
}