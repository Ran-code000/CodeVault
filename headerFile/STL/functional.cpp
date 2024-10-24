C++11 引入的 <functional> 头文件包含了许多强大的工具, 允许创建和操作函数对象

1. function
function 是一个通用, 多态的函数包装器
它可以持有任何可调用的目标, 如普通函数, lambda 表达式, 绑定表达式或函数对象

#include <iostream>
#include <functional>

void freeFunction(int a) {
    cout << "Free function called with " << a << endl;
}

class Functor {
public:
    void operator()(int a) const {
        cout << "Functor called with " << a << endl;
    }
};

int main() {
    function<void(int)> func;

    // 使用普通函数
    func = freeFunction;
    func(10);

    // 使用 lambda 表达式
    func = [](int a) {
        cout << "Lambda called with " << a << endl;
    };
    func(20);

    // 使用函数对象
    Functor functor;
    func = functor;
    func(30);

    return 0;
}

2. bind
bind 创建一个新的函数对象, 将一些参数绑定到现有的函数或函数对象上

#include <iostream>
#include <functional>

void freeFunction(int a, int b) {
    cout << "Free function called with " << a << " and " << b << endl;
}

int main() {
    auto boundFunc = bind(freeFunction, placeholders::_1, 42);

    boundFunc(10); // 实际调用 freeFunction(10, 42)

    return 0;
}

3. mem_fn
mem_fn 生成一个可调用对象来调用成员函数或访问成员变量

#include <iostream>
#include <functional>

class MyClass {
public:
    void memberFunction(int a) const {
        cout << "Member function called with " << a << endl;
    }
};

int main() {
    MyClass obj;

    auto memFunc = mem_fn(&MyClass::memberFunction);
    memFunc(&obj, 10); // 等价于 obj.memberFunction(10)

    return 0;
}

标准函数对象

4. multiplies
multiplies 是一个函数对象，用于执行乘法运算

#include <iostream>
#include <functional>

int main() {
    multiplies<int> multiply;
    int result = multiply(10, 2);
    cout << "10 * 2 = " << result << endl;

    return 0;
}

5. divides
divides 是一个函数对象，用于执行除法运算

#include <iostream>
#include <functional>

int main() {
    divides<int> divide;
    int result = divide(10, 2);
    cout << "10 / 2 = " << result << endl;

    return 0;
}

6. modulus
modulus 是一个函数对象， 用于执行取模（余数）运算

#include <iostream>
#include <functional>

int main() {
    modulus<int> mod;
    int result = mod(10, 3);
    cout << "10 % 3 = " << result << endl;

    return 0;
}

7. equal_to
equal_to 是一个函数对象，用于检查两个值是否相等

#include <iostream>
#include <functional>

int main() {
    equal_to<int> equal;
    bool result = equal(10, 10);
    cout << "10 == 10: " << boolalpha << result << endl;

    result = equal(10, 20);
    cout << "10 == 20: " << boolalpha << result << endl;

    return 0;
}

8. not_equal_to
not_equal_to 是一个函数对象，用于检查两个值是否不相等

#include <iostream>
#include <functional>

int main() {
    not_equal_to<int> not_equal;
    bool result = not_equal(10, 20);
    cout << "10 != 20: " << boolalpha << result << endl;

    result = not_equal(10, 10);
    cout << "10 != 10: " << boolalpha << result << endl;

    return 0;
}

9. less
less 是一个函数对象，用于检查左操作数是否小于右操作数。

#include <iostream>
#include <functional>

int main() {
    less<int> less_than;
    bool result = less_than(10, 20);
    cout << "10 < 20: " << boolalpha << result << endl;

    result = less_than(20, 10);
    cout << "20 < 10: " << boolalpha << result << endl;

    return 0;
}

10. greater
greater 是一个函数对象，用于检查左操作数是否大于右操作数

#include <iostream>
#include <functional>

int main() {
    greater<int> greater_than;
    bool result = greater_than(20, 10);
    cout << "20 > 10: " << boolalpha << result << endl;

    result = greater_than(10, 20);
    cout << "10 > 20: " << boolalpha << result << endl;

    return 0;
}

11. less_equal
less_equal 是一个函数对象，用于检查左操作数是否小于或等于右操作数

#include <iostream>
#include <functional>

int main() {
    less_equal<int> less_equal_to;
    bool result = less_equal_to(10, 20);
    cout << "10 <= 20: " << boolalpha << result << endl;

    result = less_equal_to(20, 20);
    cout << "20 <= 20: " << boolalpha << result << endl;

    return 0;
}

12. greater_equal
greater_equal 是一个函数对象，用于检查左操作数是否大于或等于右操作数

#include <iostream>
#include <functional>

int main() {
    greater_equal<int> greater_equal_to;
    bool result = greater_equal_to(20, 10);
    cout << "20 >= 10: " << boolalpha << result << endl;

    result = greater_equal_to(20, 20);
    cout << "20 >= 20: " << boolalpha << result << endl;

    return 0;
}

13. logical_and
logical_and 是一个函数对象，用于执行逻辑与操作

#include <iostream>
#include <functional>

int main() {
    logical_and<bool> logical_and;
    bool result = logical_and(true, false);
    cout << "true && false: " << boolalpha << result << endl;

    result = logical_and(true, true);
    cout << "true && true: " << boolalpha << result << endl;

    return 0;
}

14. logical_or
logical_or 是一个函数对象，用于执行逻辑或操作

#include <iostream>
#include <functional>

int main() {
    logical_or<bool> logical_or;
    bool result = logical_or(true, false);
    cout << "true || false: " << boolalpha << result << endl;

    result = logical_or(false, false);
    cout << "false || false: " << boolalpha << result << endl;

    return 0;
}

15. logical_not
logical_not 是一个函数对象，用于执行逻辑非操作

#include <iostream>
#include <functional>

int main() {
    logical_not<bool> logical_not;
    bool result = logical_not(true);
    cout << "!true: " << boolalpha << result << endl;

    result = logical_not(false);
    cout << "!false: " << boolalpha << result << endl;

    return 0;
}

16. negate
negate 是一个函数对象，用于对数值执行取负操作

#include <iostream>
#include <functional>

int main() {
    negate<int> negate;
    int result = negate(10);
    cout << "Negate 10: " << result << endl;

    return 0;
}

使用函数对象与标准算法结合
这些函数对象在与标准算法结合使用时特别有用
举个例子，使用 accumulate 计算一个数组元素的乘积：

#include <iostream>
#include <vector>
#include <numeric> // for accumulate
#include <functional>

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};

    int product = accumulate(numbers.begin(), numbers.end(), 1, multiplies<int>());
    cout << "Product of elements: " << product << endl;

    return 0;
}
这里, 我们使用 multiplies<int> 作为二元操作函数对象来计算数组中所有元素的乘积

17. invoke
invoke 用于调用任何可调用对象, 它可以是函数指针, 成员函数指针, 函数对象或 lambda 表达式

#include <iostream>
#include <functional>

void freeFunction(int a) {
    cout << "Free function called with " << a << endl;
}

int main() {
    // 使用 invoke 调用普通函数
    invoke(freeFunction, 10);

    // 使用 invoke 调用 lambda 表达式
    auto lambda = [](int a) {
        cout << "Lambda called with " << a << endl;
    };
    invoke(lambda, 20);

    // 使用 invoke 调用成员函数
    class MyClass {
    public:
        void memberFunction(int a) const {
            cout << "Member function called with " << a << endl;
        }
    };

    MyClass obj;
    invoke(&MyClass::memberFunction, obj, 30);

    return 0;
}

18. not_fn
not_fn 返回一个逻辑否定函数对象，可以用于对其他可调用对象的结果取反

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    auto is_even = [](int n) {
        return n % 2 == 0;
    };

    auto is_odd = not_fn(is_even);

    cout << "Odd numbers: ";
    for (int n : vec) {
        if (is_odd(n)) {
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}

19. reference_wrapper
reference_wrapper 用于创建对象的引用包装器, 可以在需要传递对象引用而非拷贝的地方使用

#include <iostream>
#include <functional>
#include <vector>

void print(int& n) {
    cout << n << endl;
}

int main() {
    int x = 10;
    vector<reference_wrapper<int>> vec;
    vec.push_back(x);

    for (auto& ref : vec) {
        print(ref);
    }

    return 0;
}

20. hash
hash 提供了对标准库中各种类型的哈希支持，常用于哈希表 (如 unordered_map 和 unordered_set)

#include <iostream>
#include <functional>
#include <string>

int main() {
    string str = "Hello";
    hash<string> hash_fn;

    size_t hash_value = hash_fn(str);
    cout << "Hash value: " << hash_value << endl;

    return 0;
}

在 C++ 中, 哈希函数通常用于将数据映射到固定大小的整数值, 这些整数值通常用于快速查找, 存储和检索数据
C++ 标准库提供了一个 hash 模板类, 可以对内置类型和部分标准库类型进行哈希操作

1. 基本使用
hash 是一个模板类，对不同类型的数据进行哈希运算
以下是对基本数据类型进行哈希计算的示例：

#include <iostream>
#include <functional>
#include <string>

int main() {
    // 对整数进行哈希计算
    hash<int> hash_int;
    int int_value = 42;
    size_t int_hash = hash_int(int_value);
    cout << "Hash of int 42: " << int_hash << endl;

    // 对字符串进行哈希计算
    hash<string> hash_string;
    string str_value = "hello";
    size_t str_hash = hash_string(str_value);
    cout << "Hash of string 'hello': " << str_hash << endl;

    // 对浮点数进行哈希计算
    hash<double> hash_double;
    double double_value = 3.14;
    size_t double_hash = hash_double(double_value);
    cout << "Hash of double 3.14: " << double_hash << endl;

    return 0;
}

2. 自定义类型的哈希函数
对于用户自定义的类型, 需要自定义哈希函数
下面是一个对自定义结构体进行哈希计算的示例：

#include <iostream>
#include <functional>
#include <string>

struct Person {
    string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

namespace std {
    template<>
    struct hash<Person> {
        size_t operator()(const Person& p) const {
            size_t h1 = hash<string>{}(p.name);
            size_t h2 = hash<int>{}(p.age);
            return h1 ^ (h2 << 1); // 组合哈希值
        }
    };
}

int main() {
    Person person = {"Alice", 30};
    hash<Person> hash_person;
    size_t person_hash = hash_person(person);
    cout << "Hash of Person {name: 'Alice', age: 30}: " << person_hash << endl;

    return 0;
}

3. 在标准容器中使用哈希函数
哈希函数在标准容器(如 unordered_set 和 unordered_map)中非常有用
以下是一个使用 unordered_map 的示例：

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    unordered_map<string, int> umap;

    // 插入一些键值对
    umap["apple"] = 1;
    umap["banana"] = 2;
    umap["orange"] = 3;

    // 查找并输出元素
    string key = "banana";
    if (umap.find(key) != umap.end()) {
        cout << key << ": " << umap[key] << endl;
    } else {
        cout << key << " not found in the map." << endl;
    }

    return 0;
}

4. 对自定义类型使用 unordered_map
继续使用前面的 Person 结构体，下面是一个使用 unordered_map 的示例：

#include <iostream>
#include <unordered_map>
#include <string>

// Person 结构体定义和哈希函数定义（与前面相同）
struct Person {
    string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

namespace std {
    template<>
    struct hash<Person> {
        size_t operator()(const Person& p) const {
            size_t h1 = hash<string>{}(p.name);
            size_t h2 = hash<int>{}(p.age);
            return h1 ^ (h2 << 1); // 组合哈希值
        }
    };
}

int main() {
    unordered_map<Person, string> person_map;

    // 插入一些条目
    person_map[{"Alice", 30}] = "Engineer";
    person_map[{"Bob", 25}] = "Designer";

    // 查找并输出元素
    Person key = {"Alice", 30};
    if (person_map.find(key) != person_map.end()) {
        cout << "Person {name: 'Alice', age: 30} is an " << person_map[key] << endl;
    } else {
        cout << "Person {name: 'Alice', age: 30} not found in the map." << endl;
    }

    return 0;
}
