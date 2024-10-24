// 静态成员函数不具有这种隐含的this指针，因此更适合用作独立的比较函数。在标准库算法和容器中使用比较函数时，
// 比较函数通常需要独立于特定的类实例调用，因此静态成员函数或者非成员函数更为合适。
// 模板参数可以是类型（Type Parameter）或非类型参数（Non-type Parameter）。
//在标准库的容器和算法中，例如 priority_queue，通常需要一个比较函数或函数对象来定义元素的排序规则

// 模板参数是类型 ———— 当构造比较函数是通过函数对象 : 类名本身是自定义的类型名，直接传类名
//                   当构造比较函数是通过函数（静态成员或者非成员） : 函数名不是类型名，传 decltype(&函数名)，还需要传入实体
//                   普通函数名不是类型，为了传递它们，需要函数指针。
//                   函数指针是一个具体的类型，因此需要使用decltype(&函数名)来获取函数指针的类型。
//                   模板参数仍然是类型参数，但这个类型是函数指针类型。
//                   compare是一个普通函数，其类型为bool(*)(int, int)
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//静态成员函数
class MyClass {
public:
    static bool COMP(int a, int b) {
        return a > b; // 大顶堆
    }
};
//非成员函数
bool COMP(int a, int b) {
    return a > b; // 大顶堆
}
//函数对象（仿函数）
struct Compare {
    bool operator()(int a, int b) {
        return a > b; // 大顶堆
    }
};

int main() {
    cout << "静态成员函数：\npriority_queue<int, vector<int>, decltype(&MyClass::COMP)> pq(&MyClass::COMP);\n";
    priority_queue<int, vector<int>, decltype(&MyClass::COMP)> pq1(&MyClass::COMP);
    pq1.push(3);
    pq1.push(1);
    pq1.push(4);
    pq1.push(1);
    pq1.push(5);
    while (!pq1.empty()) cout << pq1.top() << " ", pq1.pop();

    cout << "\n非成员函数：\npriority_queue<int, vector<int>, decltype(&COMP)> pq(COMP);\n";
    priority_queue<int, vector<int>, decltype(&COMP)> pq2(COMP);
    pq2.push(3);
    pq2.push(1);
    pq2.push(4);
    pq2.push(1);
    pq2.push(5);
    while (!pq2.empty()) cout << pq2.top() << " ", pq2.pop();

    cout << "\n函数对象（仿函数）：\npriority_queue<int, vector<int>, Compare> pq;\n";
    priority_queue<int, vector<int>, Compare> pq3;
    pq3.push(3);
    pq3.push(1);
    pq3.push(4);
    pq3.push(1);
    pq3.push(5);
    while (!pq3.empty()) cout << pq3.top() << " ", pq3.pop();

    cout << "\nLambda ：\npriority_queue<int, vector<int>, decltype(compare)> pq(compare);\n";
    auto compare = [](int a, int b) { return a > b; }; // 大顶堆
    priority_queue<int, vector<int>, decltype(compare)> pq4(compare);
    pq4.push(3);
    pq4.push(1);
    pq4.push(4);
    pq4.push(1);
    pq4.push(5);
    while (!pq4.empty()) cout << pq4.top() << " ", pq4.pop();
    return 0;
}
