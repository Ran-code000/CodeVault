<bitset> 是 C++ 标准库中的一个模板类, 用于处理固定大小的二进制序列
bitset 提供了一种方便的方法来存储和操作位(bit)以下是 bitset 的一些主要用法及其详细解释：

1. 创建 bitset
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b1; // 默认初始化，所有位为0
    bitset<8> b2(42); // 从整数初始化
    bitset<8> b3("101010"); // 从字符串初始化

    // 输出各 bitset
    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;
    cout << "b3: " << b3 << endl;

    return 0;
}

2. 设置和重置位
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b("00000000");

    b.set(); // 设置所有位为1
    cout << "After b.set(): " << b << endl;

    b.reset(); // 重置所有位为0
    cout << "After b.reset(): " << b << endl;

    b.set(3); // 设置第3位为1（从0开始计数）
    cout << "After b.set(3): " << b << endl;

    b.reset(3); // 重置第3位为0
    cout << "After b.reset(3): " << b << endl;

    b.flip(); // 翻转所有位
    cout << "After b.flip(): " << b << endl;

    b.flip(1); // 翻转第1位
    cout << "After b.flip(1): " << b << endl;

    return 0;
}

3. 访问位
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b("10101010");

    for (size_t i = 0; i < b.size(); ++i) {
        cout << "b[" << i << "]: " << b[i] << endl;
    }

    // 使用测试位
    cout << "b.test(3): " << b.test(3) << endl; // 检查第3位是否为1

    return 0;
}

4. 位计数和容量
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b("10101010");

    cout << "b.count(): " << b.count() << endl; // 计算为1的位数
    cout << "b.size(): " << b.size() << endl; // bitset的大小

    return 0;
}

5. 位操作
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b1("01010101");
    bitset<8> b2("00110011");

    cout << "b1 & b2: " << (b1 & b2) << endl; // 按位与
    cout << "b1 | b2: " << (b1 | b2) << endl; // 按位或
    cout << "b1 ^ b2: " << (b1 ^ b2) << endl; // 按位异或

    return 0;
}

6. 字符串和数字转换
#include <bitset>
#include <iostream>
#include <string>

int main() {
    bitset<8> b("10101010");

    // 转换为字符串
    string bit_str = b.to_string();
    cout << "bit_str: " << bit_str << endl;

    // 转换为整数
    unsigned long bit_num = b.to_ulong();
    cout << "bit_num: " << bit_num << endl;

    return 0;
}

7. 逻辑操作
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b1("10101010");
    bitset<8> b2("01010101");

    cout << "b1 == b2: " << (b1 == b2) << endl;
    cout << "b1 != b2: " << (b1 != b2) << endl;

    return 0;
}

8. 进制转换
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b1("10101010");

    cout << "Decimal: " << b1.to_ulong() << endl;
    cout << "Hexadecimal: " << hex << b1.to_ulong() << endl;
    cout << "Octal: " << oct << b1.to_ulong() << endl;

    return 0;
}

9. 位范围操作
#include <bitset>
#include <iostream>

int main() {
    bitset<8> b1("10101010");

    // 检查所有位是否为1
    cout << "b1.all(): " << b1.all() << endl;

    // 检查是否有任意位为1
    cout << "b1.any(): " << b1.any() << endl;

    // 检查是否没有位为1
    cout << "b1.none(): " << b1.none() << endl;

    return 0;
}
以上示例涵盖了 bitset 的主要用法, 通过这些操作, 你可以高效地处理和操作固定大小的二进制序列

