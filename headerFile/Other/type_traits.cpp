<type_traits> 是一个 C++ 标准库头文件，它包含了一系列模板类和模板函数，
这些模板类和模板函数用于在编译时对类型信息进行查询和操作。
这些工具通常被用于模板元编程中，允许程序员根据类型特征条件性地编译代码。

以下是 <type_traits> 中部分常用的工具和它们的用法，以及一些示例代码：

类型属性(Type Traits)
类型类别(Primary Type Categories)

is_void<T>: 检查 T 是否是 void 类型。
is_integral<T>: 检查 T 是否是整数类型。
is_floating_point<T>: 检查 T 是否是浮点类型。
is_array<T>: 检查 T 是否是数组类型。
is_pointer<T>: 检查 T 是否是指针。
is_reference<T>: 检查 T 是否是引用。
is_enum<T>: 检查 T 是否是枚举。
is_union<T>: 检查 T 是否是联合。
is_class<T>: 检查 T 是否是类。
is_function<T>: 检查 T 是否是函数。

类型属性(Type Properties)

is_const<T>: 检查 T 是否是 const 类型。
is_volatile<T>: 检查 T 是否是 volatile 类型。
is_trivial<T>: 检查 T 是否是平凡类型。
is_trivially_copyable<T>: 检查 T 是否是平凡可拷贝类型。
is_standard_layout<T>: 检查 T 是否具有标准布局。
is_pod<T>: 检查 T 是否是 POD(Plain Old Data)类型。
is_literal_type<T>: 检查 T 是否是字面量类型。
is_empty<T>: 检查 T 是否是空类（没有非静态数据成员）。
is_polymorphic<T>: 检查 T 是否是多态类（有虚函数）。
is_abstract<T>: 检查 T 是否是抽象类（有纯虚函数）。
类型关系(Type Relations)

is_same<T, U>: 检查 T 和 U 是否是相同类型。
is_base_of<Base, Derived>: 检查 Base 是否是 Derived 的基类。
is_convertible<From, To>: 检查 From 类型是否可以转换为 To 类型。
类型修改(Type Modifications)
remove_const<T>: 移除 T 的 const 限定。
remove_volatile<T>: 移除 T 的 volatile 限定。
remove_cv<T>: 移除 T 的 const 和 volatile 限定。
add_const<T>: 给 T 添加 const 限定。
add_volatile<T>: 给 T 添加 volatile 限定。
add_cv<T>: 给 T 添加 const 和 volatile 限定。
操作结果类型(Operation on Types)
decay<T>: 类似于函数参数推导时的类型转换。
enable_if<B, T>: 如果布尔常数 B 为 true,则提供类型 T,否则不提供类型。

示例代码

#include <type_traits>
#include <iostream>

// 使用 enable_if 作为函数模板的返回类型
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
factorial(T n) {
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

int main() {
    static_assert(std::is_integral<int>::value, "Int is an integral type.");

    // 使用 remove_const 来移除 const 限定
    typedef std::remove_const<const int>::type NonConstInt;
    static_assert(std::is_same<int, NonConstInt>::value, "Type is the same.");

    // 使用 is_same 检查两个类型是否相同
    static_assert(std::is_same<int, unsigned int>::value == false, "Types are not the same.");

    // 使用 is_convertible 检查类型是否可转换
    static_assert(std::is_convertible<int, double>::value, "int can be converted to double");

    std::cout << "Factorial of 5 is " << factorial(5) << std::endl;

    return 0;
}
上面的代码段中，我们通过 enable_if 来限制只有当 factorial 函数的模板参数 T 是整数类型时，函数才有效。
我们还使用了 static_assert 和各种其他类型特征来在编译时进行类型检查。

