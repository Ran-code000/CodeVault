stringstream 是 C++ 标准库中的一个类，位于 <sstream> 头文件中
它提供了一个流类, 用于在内存中操作字符串, 以流的方式进行读写操作

1. 创建 stringstream 对象
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    return 0;
}

2. 向 stringstream 写入数据
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    ss << "Hello, " << "world!" << ' ' << 2024;
    cout << ss.str() << endl; // 输出: Hello, world! 2024
    return 0;
}

3. 从 stringstream 读取数据
#include <iostream>
#include <sstream>

int main() {
    stringstream ss("123 456 789");
    int a, b, c;
    ss >> a >> b >> c;
    cout << a << " " << b << " " << c << endl; // 输出: 123 456 789
    return 0;
}

4. 清空 stringstream 的内容
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    ss << "Hello, world!";
    ss.str(""); // 清空内容
    ss << "New content";
    cout << ss.str() << endl; // 输出: New content
    return 0;
}

5. 重置 stringstream
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    ss << "123";
    int num;
    ss >> num;
    cout << num << endl; // 输出: 123

    ss.clear(); // 重置状态标志
    ss.str(""); // 清空内容

    ss << "456";
    ss >> num;
    cout << num << endl; // 输出: 456
    return 0;
}

6. 使用 stringstream 进行格式化输出
#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    stringstream ss;
    ss << setw(10) << setfill('0') << 42;
    cout << ss.str() << endl; // 输出: 0000000042
    return 0;
}

7. 将 stringstream 转换为 string 并使用
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    ss << "Some text and numbers: " << 12345;
    string result = ss.str();
    cout << result << endl; // 输出: Some text and numbers: 12345
    return 0;
}

8. 从 string 初始化 stringstream
#include <iostream>
#include <sstream>

int main() {
    string str = "Initial string content";
    stringstream ss(str);
    cout << ss.str() << endl; // 输出: Initial string content
    return 0;
}

9. 使用 stringstream 进行类型转换
#include <iostream>
#include <sstream>

int main() {
    stringstream ss;
    int num = 100;
    ss << num;
    string str = ss.str();
    cout << "String: " << str << endl; // 输出: String: 100

    ss.str("200");
    ss >> num;
    cout << "Number: " << num << endl; // 输出: Number: 200
    return 0;
}

10. 在 stringstream 中使用 getline 读取一行
#include <iostream>
#include <sstream>

int main() {
    stringstream ss("First line\nSecond line\nThird line");
    string line;

    while (getline(ss, line)) {
        cout << line << endl;
    }

    // 输出:
    // First line
    // Second line
    // Third line
    
    return 0;
}