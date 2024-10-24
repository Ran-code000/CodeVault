<string> 是 C++ 标准库中的一个类, 用于处理字符串, 它提供了丰富的成员函数和操作符来处理和操作字符串

1. 创建和初始化字符串
#include <string>
#include <iostream>

int main() {
    string str1; // 默认构造函数，空字符串
    string str2("Hello, World!"); // C风格字符串初始化
    string str3(str2); // 拷贝构造函数
    string str4(5, 'A'); // 用字符'A'初始化5次

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl;

    return 0;
}

2. 字符串连接
#include <string>
#include <iostream>

int main() {
    string str1 = "Hello";
    string str2 = "World";

    // 使用 + 运算符
    string str3 = str1 + ", " + str2 + "!";
    cout << "str3: " << str3 << endl;

    // 使用 += 运算符
    str1 += " ";
    str1 += str2;
    cout << "str1: " << str1 << endl;

    return 0;
}

3. 访问字符
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    // 使用下标运算符访问字符
    cout << "str[0]: " << str[0] << endl;

    // 使用 at 方法
    cout << "str.at(1): " << str.at(1) << endl;

    return 0;
}

4. 大小和容量
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    // 获取字符串长度
    cout << "Length: " << str.length() << endl;
    cout << "Size: " << str.size() << endl;

    // 获取字符串容量
    cout << "Capacity: " << str.capacity() << endl;

    // 检查字符串是否为空
    cout << "Is empty: " << str.empty() << endl;

    return 0;
}

5. 修改字符串
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    // 替换字符
    str[7] = 'w';
    cout << "After replace: " << str << endl;

    // 插入字符串
    str.insert(7, "beautiful ");
    cout << "After insert: " << str << endl;

    // 删除字符
    str.erase(7, 10);
    cout << "After erase: " << str << endl;

    // 替换子字符串
    str.replace(7, 5, "Earth");
    cout << "After replace substring: " << str << endl;

    return 0;
}

6. 查找和子字符串
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    // 查找字符
    size_t pos = str.find('W');
    if (pos != string::npos) {
        cout << "'W' found at position: " << pos << endl;
    }

    // 查找子字符串
    pos = str.find("World");
    if (pos != string::npos) {
        cout << "'World' found at position: " << pos << endl;
    }

    // 获取子字符串
    string substr = str.substr(7, 5);
    cout << "Substring: " << substr << endl;

    return 0;
}

7. 比较字符串
#include <string>
#include <iostream>

int main() {
    string str1 = "Hello";
    string str2 = "World";

    // 使用比较运算符
    if (str1 == str2) {
        cout << "str1 is equal to str2" << endl;
    } else {
        cout << "str1 is not equal to str2" << endl;
    }

    if (str1 < str2) {
        cout << "str1 is less than str2" << endl;
    }

    // 使用 compare 方法
    int result = str1.compare(str2);
    if (result == 0) {
        cout << "str1 is equal to str2" << endl;
    } else if (result < 0) {
        cout << "str1 is less than str2" << endl;
    } else {
        cout << "str1 is greater than str2" << endl;
    }

    return 0;
}

8. 转换为 C 风格字符串
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    const char* c_str = str.c_str();
    cout << "C-style string: " << c_str << endl;

    return 0;
}

9. 字符串拼接
#include <string>
#include <iostream>
#include <sstream>

int main() {
    string str1 = "Hello";
    string str2 = "World";
    string str3 = "2024";

    // 使用流操作符拼接字符串
    ostringstream oss;
    oss << str1 << ", " << str2 << " - " << str3;
    string result = oss.str();

    cout << "Concatenated string: " << result << endl;

    return 0;
}

10. 迭代器
#include <string>
#include <iostream>

int main() {
    string str = "Hello, World!";

    // 使用迭代器遍历字符串
    for (string::iterator it = str.begin(); it != str.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 使用反向迭代器遍历字符串
    for (string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    return 0;
}

11. 字符串流
#include <string>
#include <iostream>
#include <sstream>

int main() {
    string str = "123 456 789";
    istringstream iss(str);

    int a, b, c;
    iss >> a >> b >> c;

    cout << "Extracted integers: " << a << ", " << b << ", " << c << endl;

    return 0;
}

12. 转换大小写
#include <string>
#include <iostream>
#include <algorithm>

int main() {
    string str = "Hello, World!";

    // 转换为大写
    transform(str.begin(), str.end(), str.begin(), ::toupper);//::toupper 提供了全局命名空间中的 toupper 函数。
    cout << "Uppercase: " << str << endl;

    // 转换为小写
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout << "Lowercase: " << str << endl;

    return 0;
}

13. 清空和交换字符串
#include <string>
#include <iostream>

int main() {
    string str1 = "Hello";
    string str2 = "World";

    // 交换字符串
    str1.swap(str2);
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;

    // 清空字符串
    str1.clear();
    cout << "str1 after clear: " << str1 << endl;

    return 0;
}
以上示例涵盖了 string 的主要用法, 通过这些操作, 你可以高效地处理和操作字符串

