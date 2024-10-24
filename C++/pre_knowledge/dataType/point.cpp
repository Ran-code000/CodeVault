# include <iostream>

int main()
{
    const unsigned short ITEMS = 5;

    int a = 123;
    float b = 3.14;
    int intArray[ITEMS] = {1,2,3,4,5};
    char charArray[ITEMS] = {'a','b','c','d','e'};

    int *aPoint = &a;
    float *bPoint = &b;
    int *intPtr = intArray;
    char *charPtr = charArray;

    *aPoint = 456;
    *bPoint = 4.444;

    std::cout << "a的值为 : " << a << std::endl;
    std::cout << "b的值为 : " << b << std::endl;

    for(int i=0 ; i < ITEMS ; i++)
    {
        std::cout << *intPtr << " at " << static_cast<void*>(intPtr) << std::endl;
        intPtr++;
    }

    for(int i=0 ; i < ITEMS ; i++)
    {
        std::cout << *charPtr << " at " << static_cast<void*>(charPtr) << std::endl;
        charPtr++;
    }
    
    /*尽可能选择 static_cast，因为它提供了类型安全检查。只有当需要进行指针和整数之间的转换，
    或者当 static_cast 不能进行必要的转换时，才应该使用 reinterpret_cast
    1.安全级别不同：
    static_cast 是类型安全的，而 reinterpret_cast 不是。
    2.使用场景不同：
    static_cast 通常用于更常见的类型转换和类层次结构中的转换，而 reinterpret_cast 用于
    低级别的，依赖于实现的转换（比如指针和足够大的整数(unsigned long)之间的转换）。
    3.转换的严格性不同：
    reinterpret_cast 允许几乎任何的指针转换，而 static_cast 受限于类型系统的规则*/

    return 0;
}