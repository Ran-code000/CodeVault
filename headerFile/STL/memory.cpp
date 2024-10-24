C++的 <memory> 头文件包含了一些很重要的内存管理工具和智能指针的定义
以下是 <memory> 头文件中一些常用组件及其用法的详细解释和示例代码

1. unique_ptr
unique_ptr 是一种独占所有权的智能指针, 当它被销毁时, 自动释放所管理的对象

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    // 创建一个 unique_ptr 管理的动态分配的 int
    unique_ptr<int> ptr1(new int(10));
    cout << "Value: " << *ptr1 << endl;

    // 使用 make_unique 创建 unique_ptr
    auto ptr2 = make_unique<int>(20);
    cout << "Value: " << *ptr2 << endl;

    // 转移所有权
    unique_ptr<int> ptr3 = move(ptr1);
    if (!ptr1) {
        cout << "ptr1 is now null" << endl;
    }
    cout << "Value: " << *ptr3 << endl;

    return 0;
}

2. shared_ptr
shared_ptr 是一种共享所有权的智能指针, 通过引用计数来管理共享所有权的对象

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    // 创建一个 shared_ptr 管理的动态分配的 int
    shared_ptr<int> ptr1(new int(10));
    cout << "Value: " << *ptr1 << ", use count: " << ptr1.use_count() << endl;

    // 使用 make_shared 创建 shared_ptr
    auto ptr2 = make_shared<int>(20);
    cout << "Value: " << *ptr2 << ", use count: " << ptr2.use_count() << endl;

    // 共享所有权
    shared_ptr<int> ptr3 = ptr1;
    cout << "Value: " << *ptr1 << ", use count: " << ptr1.use_count() << endl;
    cout << "Value: " << *ptr3 << ", use count: " << ptr3.use_count() << endl;

    return 0;
}

3. weak_ptr
weak_ptr 是一种不拥有对象所有权的智能指针, 防止 shared_ptr 循环引用

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    shared_ptr<int> sharedPtr = make_shared<int>(10);
    weak_ptr<int> weakPtr = sharedPtr;

    cout << "Shared use count: " << sharedPtr.use_count() << endl;

    if (auto sp = weakPtr.lock()) {
        cout << "Weak pointer is valid, value: " << *sp << endl;
    } else {
        cout << "Weak pointer is expired" << endl;
    }

    sharedPtr.reset(); // 释放 shared_ptr

    if (auto sp = weakPtr.lock()) {
        cout << "Weak pointer is valid, value: " << *sp << endl;
    } else {
        cout << "Weak pointer is expired" << endl;
    }

    return 0;
}

4. allocator
allocator 提供了一个用于动态分配内存的类模板
虽然在现代 C++ 中它很少直接使用，但它仍然是理解 STL 容器的内存管理的关键

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    allocator<int> alloc; // 创建一个分配器对象

    // 分配内存但不构造对象
    int* p = alloc.allocate(1);

    // 在分配的内存上构造对象
    alloc.construct(p, 42);

    cout << "Value: " << *p << endl;

    // 销毁对象但不释放内存
    alloc.destroy(p);

    // 释放内存
    alloc.deallocate(p, 1);

    return 0;
}

5. pointer_traits
pointer_traits 是一个模板类, 为指针类型提供了类型特征信息, 主要用于泛型编程

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    using Ptr = unique_ptr<int>;
    using Traits = pointer_traits<Ptr>;

    Ptr p = make_unique<int>(42);
    cout << "Pointer value: " << *p << endl;
    cout << "Pointer element type: " << typeid(Traits::element_type).name() << endl;

    return 0;
}

6. uninitialized_copy 和 uninitialized_fill
这些函数用于在未初始化的内存中构造对象

用法和代码示例：
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    int* p = static_cast<int*>(::operator new(sizeof(int) * vec.size()));

    // 使用 uninitialized_copy 在未初始化的内存中构造对象
    uninitialized_copy(vec.begin(), vec.end(), p);

    // 打印复制的对象
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << p[i] << " ";
    }
    cout << endl;

    // 使用 uninitialized_fill 在未初始化的内存中构造对象
    uninitialized_fill(p, p + vec.size(), 10);

    // 打印填充的对象
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << p[i] << " ";
    }
    cout << endl;

    // 手动销毁对象
    destroy(p, p + vec.size());

    // 释放内存
    ::operator delete(p);

    return 0;
}

7. align
align 是一个用于对齐内存块的函数

用法和代码示例：
#include <iostream>
#include <memory>

int main() {
    alignas(16) char buffer[64]; // 确保 buffer 对齐到 16 字节
    void* ptr = buffer;

    size_t space = sizeof(buffer);
    void* aligned_ptr = align(16, sizeof(int), ptr, space);

    if (aligned_ptr) {
        cout << "Aligned pointer: " << aligned_ptr << endl;
        cout << "Remaining space: " << space << endl;
    } else {
        cout << "Alignment failed" << endl;
    }

    return 0;
}

8. raw_storage_iterator
raw_storage_iterator 是一个适配器, 用于将未初始化的内存视为输出迭代器

用法和代码示例：
#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

int main() {
    int buffer[4];
    raw_storage_iterator<int*, int> iter(buffer);

    *iter++ = 1;
    *iter++ = 2;
    *iter++ = 3;
    *iter++ = 4;

    for (int i : buffer) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
