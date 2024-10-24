# include <iostream>

class Base
{
public:
    Base()
    {
        std::cout << "Base constructor" << std::endl;
    }
    ~Base()
    {
        std::cout << "Base destructor" << std::endl;
    }
}
//只有当一个类被用作基类时才把析构函数写成虚函数

class Derived : public Base
{
public:
    Derived()
    {
        std::cout << "Derived constructor" <<std::endl;
    }
    ~Derived()
    {
        std::cout << "Derived destructor" << std::endl;
    }
}

int main()
{
    Base *b = new Derived;
    delete b;
    // 这里只会调用 Base 的析构函数，而不会调用 Derived 的析构函数。
    // 如果 Derived 类中有需要释放的资源，这将导致资源泄漏
    //基类应该改为virtual ~Base() {....};

    return 0;
}