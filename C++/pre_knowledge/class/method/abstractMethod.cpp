# include <iostream>

/*纯虚方法 (Pure Virtual Method) or 抽象方法 (Abstract Method)
纯虚方法是一种特殊的虚方法，它不提供任何实现，而是要求派生类必须提供实现。
一个包含纯虚函数的类称为抽象基类，不能直接实例化*/

class AbstractBase
{
public:
    virtual void pureVirtualFunc () = 0;
};

class ConcreteClass : public AbstractBase
{
public:
    void pureVirtualFunc () override
    {
        std::cout << "Implemented pureVirtualFunc" << std::endl;
    }
}
int main()
{
    // AbstractBase ab; // 错误: 不能实例化抽象类
    ConcreteClass cc;
    cc.pureVirtualFunc(); // 正确: ConcreteClass提供了纯虚函数的实现

    return 0;
}