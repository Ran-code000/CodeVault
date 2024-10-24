一个无符号 char 类型的变量（通常占用 1 个字节，即 8 位）可以用来存储 8 个双状态（即二进制状态，可以是 0 或 1)的设置
每一位(bit)可以表示一个双状态开关，所以 1 个字节(8 位)可以表示 8 个这样的开关。

下面通过一个 C++ 代码示例来详细解释这一点：

示例代码

#include <iostream>
#include <bitset>

int main() {
    // 创建一个无符号 char 变量，初始值为 0
    unsigned char settings = 0;

    // 定义每个状态的位位置
    const unsigned char STATE1 = 1 << 0; // 0000 0001
    const unsigned char STATE2 = 1 << 1; // 0000 0010
    const unsigned char STATE3 = 1 << 2; // 0000 0100
    const unsigned char STATE4 = 1 << 3; // 0000 1000
    const unsigned char STATE5 = 1 << 4; // 0001 0000
    const unsigned char STATE6 = 1 << 5; // 0010 0000
    const unsigned char STATE7 = 1 << 6; // 0100 0000
    const unsigned char STATE8 = 1 << 7; // 1000 0000

    // 设置某些状态
    settings |= STATE1; // 打开 STATE1
    settings |= STATE3; // 打开 STATE3
    settings |= STATE5; // 打开 STATE5
    settings |= STATE8; // 打开 STATE8

    // 打印当前的二进制状态
    cout << "Current settings: " << bitset<8>(settings) << endl;

    // 检查某些状态
    if (settings & STATE1) {
        cout << "STATE1 is ON" << endl;
    } else {
        cout << "STATE1 is OFF" << endl;
    }

    if (settings & STATE2) {
        cout << "STATE2 is ON" << endl;
    } else {
        cout << "STATE2 is OFF" << endl;
    }

    // 关闭某个状态
    settings &= ~STATE1; // 关闭 STATE1

    // 打印更新后的二进制状态
    cout << "Updated settings: " << bitset<8>(settings) << endl;

    return 0;
}

代码解释
1. 定义无符号 char 变量：
unsigned char settings = 0;
settings 变量初始值为 0 (即 0000 0000)

2. 定义每个状态的位位置：

const unsigned char STATE1 = 1 << 0; // 0000 0001
const unsigned char STATE2 = 1 << 1; // 0000 0010
const unsigned char STATE3 = 1 << 2; // 0000 0100
const unsigned char STATE4 = 1 << 3; // 0000 1000
const unsigned char STATE5 = 1 << 4; // 0001 0000
const unsigned char STATE6 = 1 << 5; // 0010 0000
const unsigned char STATE7 = 1 << 6; // 0100 0000
const unsigned char STATE8 = 1 << 7; // 1000 0000
每个常量标志着一个特定的位位置，用于表示不同的状态。

3. 设置状态：
settings |= STATE1; // 打开 STATE1
settings |= STATE3; // 打开 STATE3
settings |= STATE5; // 打开 STATE5
settings |= STATE8; // 打开 STATE8
使用按位或 (|=) 操作符设置特定位为 1。

4. 打印当前的二进制状态：
cout << "Current settings: " << bitset<8>(settings) << endl;
使用 bitset<8> 将 settings 转换为二进制格式打印出来。

5. 检查状态：
if (settings & STATE1) {
    cout << "STATE1 is ON" << endl;
} else {
    cout << "STATE1 is OFF" << endl;
}
使用按位与 (&) 操作符检查特定位是否为 1。

6. 关闭状态：
settings &= ~STATE1; // 关闭 STATE1
使用按位与和按位取反 (~) 操作符将特定位关闭。

7. 打印更新后的二进制状态：
cout << "Updated settings: " << bitset<8>(settings) << endl;
通过这种方式，一个无符号 char 类型变量可以存储多达 8 个独立的二进制状态，每个位都可以被单独设置或清除。
这种技术在需要紧凑表示多个布尔值的场景中非常有用。

