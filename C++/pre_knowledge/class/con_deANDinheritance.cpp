# include <iostream>
# include <string>

//展示基类和子类构造器和析构器的用法过程

/*对象subclass的类型是SubClass，不涉及到基类指针或引用指向派生类对象的情况,
因此这段代码基类析构器没写virtual却仍然执行了子类析构器，
当一个派生类对象在其生命周期结束时被销毁，首先调用的是派生类的析构函数，然后是基类的析构函数。这是自动发生的，
因为编译器知道确切的对象类型。
*/

class BaseClass
{
public:
    BaseClass();
    ~BaseClass();

    void doSomething();
};

class SubClass : public BaseClass
{
public:
    SubClass();
    ~SubClass();
};

BaseClass::BaseClass()
{
    std::cout << "进入基类构造器......\n";
    std::cout << "我在基类里面干了某些事......\n\n";
}

BaseClass::~BaseClass()
{
    std::cout << "进入基类析构器.......\n";
    std::cout << "我在基类析构器内也干了某些事......\n\n";
}

void BaseClass::doSomething()
{
    std::cout << "我干了某些事......\n\n";
}

SubClass::SubClass()
{
    std::cout << "进入子类构造器......\n";
    std::cout << "我在子类构造器里面还干了某些事.......\n\n";
}

SubClass::~SubClass()
{
    std::cout << "进入子类析构器......\n";
    std::cout << "我在子类析构器里面干了某些事......\n\n";
}

int main()
{
    SubClass subclass;
    subclass.doSomething();

    std::cout << "完事，收工！\n";

    return 0;
}
