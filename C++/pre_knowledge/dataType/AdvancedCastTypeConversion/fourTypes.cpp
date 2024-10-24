高级强制类型转换（也称为类型转换运算符或强制类型转换运算符）提供了比 C 风格类型转换更明确和更安全的转换方式。
C++ 提供了四种高级强制类型转换：

1.static_cast
2.dynamic_cast
3.const_cast
4.reinterpret_cast
它们的作用和使用场景各不相同：

1. static_cast
static_cast 是用来处理编译时类型转换的，它可以在相关类型之间进行转换，比如将 float 转换为 int,
或者将基类指针转换为派生类指针（向下转型），前提是这种转换在编译时是安全的。

int main() {
    float f = 3.5f;
    // 将 float 转换为 int
    int i = static_cast<int>(f); // i 的值将是 3

    // 基类和派生类之间的转换
    class Base {};
    class Derived : public Base {};

    Base* b = new Derived();
    // 向下转型，将 Base 类型的指针转换为 Derived 类型的指针
    Derived* d = static_cast<Derived*>(b);
    return 0;
}

2. dynamic_cast
dynamic_cast 主要用于处理多态类型。当你有一个基类指针或引用，且需要将其转换为派生类指针或引用时，
你可以使用 dynamic_cast。如果转换是安全的(即对象确实是目标类型的实例)，转换成功；
如果不安全，则返回空指针(nullptr对指针类型)或抛出异常(std::bad_cast对引用类型)。

class Base {
public:
    virtual void print() { cout << "Base" << endl; }
};

class Derived : public Base {
public:
    void print() override { cout << "Derived" << endl; }
};

int main() {
    Base* b = new Derived();
    // 使用 dynamic_cast 进行向下转型
    Derived* d = dynamic_cast<Derived*>(b);
    if (d != nullptr) {
        d->print(); // 输出 "Derived"
    }
    return 0;
}

tips:
Base* b = new Derived1;
Derived1* d1 = dynamic_cast<Derived1*>(b); // 成功：b 实际指向 Derived1 对象
Derived2* d2 = dynamic_cast<Derived2*>(b); // 失败：b 不指向 Derived2 对象，返回 nullptr

3. const_cast
const_cast 用于修改类型的 const 或 volatile 属性。通常用于去除 const 属性，以便对原本被声明为 const 的变量进行写操作。

int main() {
    const int ci = 10;
    // 去除变量 ci 的 const 属性
    int* modifiable = const_cast<int*>(&ci);
    *modifiable = 20; 
    实际上这样做是未定义行为,因为const_cast 被用来去除变量 ci 的 const 属性。
    然而，虽然 const_cast 可以用来移除变量的 const(或 volatile)限定符,
    但它只应该用在指向非 const 数据的指针或引用上，临时地去除它们的 const 限定符。在本例,ci 本身是一个 const 整数，
    它的值在编译时被设定为不可更改。
    例如：
void process(int* ptr);

int main() {
    int value = 10; //注意此时value不是const
    const int* ptr = &value;

    // 正确使用 const_cast
    process(const_cast<int*>(ptr));

    return 0;
}

void process(int* ptr) {
    // 在这里，ptr 指向的数据不是 const，所以我们可以安全地修改它
    *ptr = 20;
}
    return 0;
}

4. reinterpret_cast
reinterpret_cast 提供了低层次上的、实现定义的重新解释类型的能力。它可以将任何指针转换为任何其他指针类型
(例如，将 int* 转换为 char*),也可以将指针转换为足够大的整数类型。
使用 reinterpret_cast 需要小心，因为它可能会产生平台依赖的代码。

int main() {
    int* p = new int(65);
    // 将 int* 转换为 char*，并不改变数据本身
    char* ch = reinterpret_cast<char*>(p);
    cout << *ch << endl; // 可能的输出是 "A"，取决于系统的字节序
    return 0;
}
高级强制类型转换比 C 风格转换更安全，因为它们更加明确，并且每种转换都有其特定的用途。
使用高级强制类型转换可以帮助避免类型转换中的隐式错误，并使代码的意图更加清晰。

tips:
强制类型转换不会创建一个副本拷贝,对于指针类型他们指向同一个地址,切记delete一个就好,不要重复释放

