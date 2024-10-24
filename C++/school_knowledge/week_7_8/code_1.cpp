#include <iostream>
#include <cstring>
using namespace std;
class Integer{
    int x;
    int n;
    int *a;
public:
    Integer(int x = 0, int n = 1) : x(x), n(n){
        a = new int[n];
        for(int i = 0; i < n; i++) a[i] = i;
    };
    ~Integer(){
        delete[] a;
    }
    Integer operator + (const Integer &Int){
        return Integer(x + Int.x);
    }
    Integer operator - (const Integer &Int){
        return Integer(x - Int.x);
    }
    Integer operator * (const Integer &Int){
        return Integer(x * Int.x);
    }
    Integer operator / (const Integer &Int){
        return Integer(x / Int.x);
    }
    Integer operator - (){
        return Integer(-x);
    }
    Integer& operator ++ (){
        //前置
        x++;
        return *this;
    }
    Integer operator ++ (int){
        //后置
        return Integer(x++);
    }
    Integer& operator = (const Integer &other){
        //深拷贝（官方指南）
        if(this != &other){
            x = other.x;
            if(n != other.n){
                delete[] a;
                n = 0;
                a = nullptr;
                a = new int[other.n];
                memcpy(a, other.a, sizeof(int) * n);
                n = other.n;
            }
        }
        return *this;
    }
    Integer& operator += (const Integer &other){
        *this = this -> operator + (other);
        //x += other.x;
        return *this;
    }
    Integer& operator -= (const Integer &other){
        *this = this -> operator - (other);
        //x -= other.x;
        return *this;
    }
    Integer& operator *= (const Integer &other){
        *this = this -> operator * (other);
        //x *= other.x;
        return *this;
    }
    Integer& operator /= (const Integer &other){
        *this = this -> operator / (other);
        //x /= other.x;
        return *this;
    }
    Integer(Integer &&other){
        x = other.x, other.x = 0;
        n = other.n, other.n = 0;
        a = other.a, other.a = nullptr;
    }
    Integer& operator = (Integer &&other){
        if(this != &other){
            if(other.a){
                delete[] a;
                a = other.a, other.a = nullptr;
                n = other.n, other.n = 0;
                x = other.x, other.x = 0;
            }
        }
        return *this;
    }
};
int main(){

    return 0;
}