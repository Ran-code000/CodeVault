<typeinfo> 是 C++ 标准库中的一个头文件,主要用于支持运行时类型识别(RTTI)
它提供了一些工具和类来获取类型信息，其中最主要的类是 type_info。


主要内容
1. type_info 类
2. typeid 操作符
3. bad_typeid 异常类

1. type_info 类
type_info 类包含了有关类型的信息，主要提供以下方法：

name(): 返回一个字符指针，指向类型的名称（具体名称由实现定义）。
before(const type_info& rhs) const: 如果当前类型在排序上位于 rhs 之前，则返回 true。
operator== 和 operator!=: 用于比较两个 type_info 对象。
hash_code() const: 返回一个代表类型的哈希值。

示例代码：
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main() {
    Base base;
    Derived derived;
    Base* basePtr = &derived;

    const type_info& baseInfo = typeid(base);
    const type_info& derivedInfo = typeid(derived);
    const type_info& basePtrInfo = typeid(basePtr);
    const type_info& derefBasePtrInfo = typeid(*basePtr);

    cout << "base type: " << baseInfo.name() << endl;
    cout << "derived type: " << derivedInfo.name() << endl;
    cout << "basePtr type: " << basePtrInfo.name() << endl;
    cout << "Dereferenced basePtr type: " << derefBasePtrInfo.name() << endl;

    // 比较类型信息
    cout << "base and derived are " << (baseInfo == derivedInfo ? "same" : "different") << endl;
    cout << "base and dereferenced basePtr are " << (baseInfo == derefBasePtrInfo ? "same" : "different") << endl;

    // 使用before方法
    cout << "base before derived: " << baseInfo.before(derivedInfo) << endl;

    // 使用hash_code方法
    cout << "base hash code: " << baseInfo.hash_code() << endl;
    cout << "derived hash code: " << derivedInfo.hash_code() << endl;

    return 0;
}

2. typeid 操作符
typeid 操作符用于获取类型信息，返回一个 type_info 对象。
它可以作用于类型、对象或指针/引用。typeid 在多态对象上尤为有用，因为它能获取实际对象的类型。

示例代码：
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main() {
    Base base;
    Derived derived;
    Base* basePtr = &derived;

    cout << "Type of base: " << typeid(base).name() << endl;
    cout << "Type of derived: " << typeid(derived).name() << endl;
    cout << "Type of basePtr: " << typeid(basePtr).name() << endl;
    cout << "Type of *basePtr: " << typeid(*basePtr).name() << endl;

    return 0;
}

3. bad_typeid 异常类
bad_typeid 异常类在尝试获取空指针引用的类型信息时会被抛出。

示例代码：
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main() {
    try {
        Base* basePtr = nullptr;
        cout << "Type of *basePtr: " << typeid(*basePtr).name() << endl;
    } catch (const bad_typeid& e) {
        cerr << "Caught bad_typeid: " << e.what() << endl;
    }

    return 0;
}
在这段代码中，如果 basePtr 是空指针，那么 typeid(*basePtr) 会抛出 bad_typeid 异常。


综合示例
结合使用 type_info、typeid 和 bad_typeid 的综合示例：
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main() {
    Base base;
    Derived derived;
    Base* basePtr = &derived;

    // 使用typeid获取类型信息
    const type_info& baseInfo = typeid(base);
    const type_info& derivedInfo = typeid(derived);
    const type_info& basePtrInfo = typeid(basePtr);
    const type_info& derefBasePtrInfo = typeid(*basePtr);

    cout << "Type of base: " << baseInfo.name() << endl;
    cout << "Type of derived: " << derivedInfo.name() << endl;
    cout << "Type of basePtr: " << basePtrInfo.name() << endl;
    cout << "Type of *basePtr: " << derefBasePtrInfo.name() << endl;

    // 比较类型信息
    cout << "base and derived are " << (baseInfo == derivedInfo ? "same" : "different") << endl;
    cout << "base and dereferenced basePtr are " << (baseInfo == derefBasePtrInfo ? "same" : "different") << endl;

    // 使用before方法
    cout << "base before derived: " << baseInfo.before(derivedInfo) << endl;

    // 使用hash_code方法
    cout << "base hash code: " << baseInfo.hash_code() << endl;
    cout << "derived hash code: " << derivedInfo.hash_code() << endl;

    // 捕捉bad_typeid异常
    try {
        Base* nullPtr = nullptr;
        cout << "Type of *nullPtr: " << typeid(*nullPtr).name() << endl;
    } catch (const bad_typeid& e) {
        cerr << "Caught bad_typeid: " << e.what() << endl;
    }

    return 0;
}
这个综合示例展示了如何使用 type_info 类的各种方法、typeid 操作符以及捕捉 bad_typeid 异常。
