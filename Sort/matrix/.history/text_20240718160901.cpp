#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <ctime>
using namespace std;
class A;
class B;
class C;
class D;
class E;
class F;
class A {
public:
      class IVisitor {
          public:
          //纯虚函数，抽象基类
          virtual void visit(A *) = 0;
          virtual void visit(B *) = 0;
          virtual void visit(C *) = 0;
          virtual void visit(D *) = 0;
          virtual void visit(E *) = 0;
          virtual void visit(F *) = 0;
      };
      virtual void Accept(IVisitor *vis) {
          vis->visit(this);
      }
      virtual ~A() {}
};

class B : public A {
public :
    void Accept(IVisitor *vis) override { vis->visit(this);}
};

class C : public A {
public :
    void Accept(IVisitor *vis) override { vis->visit(this);}
};

class D : public A {
public :
    void Accept(IVisitor *vis) override { vis->visit(this);}
};

class E : public A {
public :
    void Accept(IVisitor *vis) override { vis->visit(this);}
};

class F : public A {
public :
    void Accept(IVisitor *vis) override { vis->visit(this);}
};

class OutputVisitor : public A::IVisitor {
public :
    //重载
    virtual void visit(A *) {
        cout << "This is base class " << endl;
    }
    virtual void visit(B *) {
        cout << "This is B class " << endl;
    }
    virtual void visit(C *) {
        cout << "This is C class " << endl;
    }
    virtual void visit(D *) {
        cout << "This is D class " << endl;
    }
    virtual void visit(E *) {
        cout << "This is E class " << endl;
    }
    virtual void visit(F *) {
        cout << "This is F class " << endl;
    }
};

class CalcVisitor : public A::IVisitor {
public :
    CalcVisitor(int val = 1) : val(val) {}
    virtual void visit(A *) {}
    virtual void visit(B *) {
        val += 5;
        cout << "val += 5 " << endl;
    }
    virtual void visit(C *) {
        val *= 2;
        cout << "val *= 2 " << endl;
    }
    virtual void visit(D *) {
        val -= 4;
        cout << "val -= 4 " << endl;
    }
    virtual void visit(E *) {
        val += 6;
        cout << "val += 6 " << endl;
    }
    virtual void visit(F *) {
        val -= 7;
        cout << "val -= 7 " << endl;
    }
    int val;
};
int main() {
    srand(time(0));
    A *arr[10];
    for (int i = 0; i < 10; i++) {
        switch (rand() % 5) {
            case 0 : arr[i] = new B(); break;
            case 1 : arr[i] = new C(); break;
            case 2 : arr[i] = new D(); break;
            case 3 : arr[i] = new E(); break;
            case 4 : arr[i] = new F(); break;
        }
    }
    OutputVisitor vis;
    CalcVisitor cvis;
    for (int i = 0; i < 10; i++) {
        arr[i]->Accept(&vis);//输出
        arr[i]->Accept(&cvis);//计算
    }
    cout << "The final val is : " << cvis.val << endl;
    return 0;
}
