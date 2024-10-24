C++ 标准库中的 array 是一个用于替代普通 C 风格数组的模板类，提供了更安全和便捷的数组操作方法
array 是一个固定大小的数组容器，包含在 <array> 头文件中

1. 包含头文件
#include <iostream>
#include <array>

2. 创建 array
array<int, 5> arr1; // 创建一个大小为 5 的 int 数组
array<int, 5> arr2 = {1, 2, 3, 4, 5}; // 使用列表初始化
array<int, 5> arr3 {1, 2, 3, 4, 5}; // 使用直接初始化

3. 访问元素
通过索引访问
array<int, 5> arr = {1, 2, 3, 4, 5};
cout << arr[0] << endl; // 访问第一个元素，输出 1
cout << arr.at(1) << endl; // 访问第二个元素，输出 2，带边界检查

使用迭代器
for (auto it = arr.begin(); it != arr.end(); ++it) {
    cout << *it << " ";
}
cout << endl;

4. 修改元素
arr[0] = 10;
arr.at(1) = 20; // 使用 at 修改元素

5. 获取数组大小
cout << "Array size: " << arr.size() << endl; // 输出 5

6. 访问首尾元素
cout << "First element: " << arr.front() << endl; // 输出 10
cout << "Last element: " << arr.back() << endl; // 输出 5

7. 填充数组
arr.fill(0); // 将所有元素设置为 0

8. 交换数组内容
array<int, 5> arr4 = {5, 4, 3, 2, 1};
arr.swap(arr4); // 交换 arr 和 arr4 的内容

9. 与 C 风格数组互操作
获取底层数组指针
int* data = arr.data(); // 获取底层数组指针
cout << "First element via pointer: " << data[0] << endl; // 输出 5

10. 使用范围 for 循环
for (int value : arr) {
    cout << value << " ";
}
cout << endl;

11. array 和算法库的结合使用
可以将 array 作为参数传递给标准库的算法函数，像 sort、find 等

#include <algorithm>

int main() {
    array<int, 5> arr = {3, 1, 4, 1, 5};

    // 排序
    sort(arr.begin(), arr.end());
    for (int value : arr) {
        cout << value << " "; // 输出 1 1 3 4 5
    }
    cout << endl;

    // 查找
    auto it = find(arr.begin(), arr.end(), 3);
    if (it != arr.end()) {
        cout << "Element found: " << *it << endl; // 输出 Element found: 3
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}

12. 其他有用的方法
array 的比较运算符
array<int, 3> arr5 = {1, 2, 3};
array<int, 3> arr6 = {1, 2, 3};
array<int, 3> arr7 = {4, 5, 6};

if (arr5 == arr6) {
    cout << "arr5 and arr6 are equal" << endl; // 输出
}

if (arr5 != arr7) {
    cout << "arr5 and arr7 are not equal" << endl; // 输出
}

get 获取元素
array<int, 3> arr8 = {7, 8, 9};
cout << get<0>(arr8) << endl; // 输出 7
cout << get<1>(arr8) << endl; // 输出 8

tuple_size 和 tuple_element

array<int, 4> arr9 = {1, 2, 3, 4};
cout << "Array size: " << tuple_size<decltype(arr9)>::value << endl; // 输出 4

using ElementType = tuple_element<1, decltype(arr9)>::type;
ElementType element = arr9[1];
cout << "Second element type and value: " << element << endl; // 输出 2
