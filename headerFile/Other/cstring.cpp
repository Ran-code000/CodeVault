/*<cstring> 头文件在 C++ 中用于处理 C 风格的字符串。它包含了一系列操作以 null 结尾的字符串的函数。
这些字符串本质上是字符数组，最后一个字符后面跟着一个 \0(null 字符)，用以标示字符串的结束。

以下是 <cstring> 中定义的函数及其用法的示例:

1.strlen
返回字符串的长度，不包括结束的 null 字符。

#include <cstring>
#include <iostream>

int main() {
    const char* str = "Hello, World!";
    std::cout << "Length of str is: " << std::strlen(str) << std::endl;
    return 0;
}

2.strcpy 和 strncpy
strcpy 复制一个字符串到另一个字符串。strncpy 也是复制字符串，但它会限制复制的最大长度，
并且在目标数组中剩余的部分会填充 null 字符。

#include <cstring>
#include <iostream>

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    // 安全的做法是使用 strncpy 防止缓冲区溢出
    std::strncpy(dest, src, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0'; // 确保有 null 结尾

    std::cout << "Copied string: " << dest << std::endl;
    return 0;
}

3.strcat 和 strncat
strcat 将一个字符串追加到另一个字符串的末尾。strncat 也是追加字符串，但它会限制追加的最大长度。

#include <cstring>
#include <iostream>

int main() {
    char dest[20] = "Hello,";
    char src[] = " World!";

    // 使用 strncat 防止缓冲区溢出
    std::strncat(dest, src, sizeof(dest) - std::strlen(dest) - 1);

    std::cout << "Concatenated string: " << dest << std::endl;
    return 0;
}

4.strcmp 和 strncmp
strcmp 比较两个字符串。strncmp 也是比较两个字符串，但它会限制比较的最大长度。

#include <cstring>
#include <iostream>

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";

    if (std::strcmp(str1, str2) == 0) {
        std::cout << "The strings are equal." << std::endl;
    } else {
        std::cout << "The strings are not equal." << std::endl;
    }
    return 0;
}

5.strchr 和 strrchr
strchr 查找字符串中第一次出现的指定字符。strrchr 查找最后一次出现的指定字符。

#include <cstring>
#include <iostream>

int main() {
    const char* str = "Hello, World!";
    char ch = 'o';

    const char* firstOccurrence = std::strchr(str, ch);
    const char* lastOccurrence = std::strrchr(str, ch);

    if (firstOccurrence) {
        std::cout << "First occurrence of " << ch << " is at position: " << (firstOccurrence - str) << std::endl;
    }
    
    if (lastOccurrence) {
        std::cout << "Last occurrence of " << ch << " is at position: " << (lastOccurrence - str) << std::endl;
    }
    return 0;
}

6.strstr
查找一个字符串在另一个字符串中的第一次出现。

#include <cstring>
#include <iostream>

int main() {
    const char* str = "Hello, World!";
    const char* substr = "World";

    const char* occurrence = std::strstr(str, substr);

    if (occurrence) {
        std::cout << "Substring found at position: " << (occurrence - str) << std::endl;
    } else {
        std::cout << "Substring not found." << std::endl;
    }
    return 0;
}

7.strspn 和 strcspn
strspn 计算字符串中连续字符都属于指定字符集的最大段长度。strcspn 相反，计算连续字符不属于指定字符集的最大段长度。

#include <cstring>
#include <iostream>

int main() {
    const char* str = "12345abcde67890";
    const char* accept = "1234567890";

    int numChars = std::strspn(str, accept);
    std::cout << "Initial number segment length: " << numChars << std::endl;

    const char* reject = "abcde";
    numChars = std::strcspn(str, reject);
    std::cout << "Initial non-letter segment length: " << numChars << std::endl;

    return 0;
}

8.memset
用给定的字符填充内存区域。

#include <cstring>
#include <iostream>

int main() {
    char str[15];
    std::memset(str, 'A', sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0'; // 确保 null 结尾

    std::cout << "Memset string: " << str << std::endl;
    return 0;
}


9.memcpy 和 memmove
memcpy 从源内存区域复制字节到目标内存区域。memmove 类似，但它能处理源和目标内存区域重叠的情况。

memcpy 和 memmove 都是 C 标准库中的函数，用于内存块的拷贝。它们的主要区别在于处理源内存和目标内存重叠的情况。

memcpy 函数假设源内存区域和目标内存区域不重叠,因此它可能在复制时采用更高效的方法。如果源和目标内存区域重,
memcpy 的行为是未定义的，可能会导致数据损坏。

memmove 函数是安全的,即使源内存区域和目标内存区域重叠,它也能正确地处理。
memmove 会先将源内存区域的数据拷贝到一个临时区域，然后再从临时区域拷贝到目标内存区域，
或者采取其他不依赖直接拷贝的手段来避免数据的损坏。

下面是一个示例，展示了 memcpy 和 memmove 在使用中可能出现的行为差异：

#include <iostream>
#include <cstring>

int main() {
    char source[] = "Hello World";

    // 使用 memcpy 进行重叠拷贝可能导致未定义行为
    std::cout << "Using memcpy with overlapping regions:\n";
    memcpy(source + 6, source, 5); // 未定义行为，因为 source 和 source + 6 重叠
    std::cout << source << std::endl; // 可能输出不是 "Hello Hello"

    // 重置 source 数组
    strcpy(source, "Hello World");

    // 使用 memmove 进行重叠拷贝是安全的
    std::cout << "Using memmove with overlapping regions:\n";
    memmove(source + 6, source, 5); // 安全的，即使区域重叠也能正确处理
    std::cout << source << std::endl; // 输出 "Hello Hello"

    return 0;
}
在这个例子中，有一个源字符串 “Hello World”。我们尝试使用 memcpy 将 “Hello” 复制到字符串的 “World” 位置，
但是因为源和目标内存区域重叠，所以这可能会导致未定义的行为，输出可能不是我们期望的 “Hello Hello”。

然后，我们重置源字符串并使用 memmove 执行相同的操作。由于 memmove 能够正确处理内存重叠的情况，
所以即使源和目标区域重叠，输出也会是预期的 “Hello Hello”。

在 C++ 中，通常更倾向于使用 C++ 标准库中的功能，如 std::copy 或 std::copy_backward(当需要处理可能重叠的范围时),
这些函数在 <algorithm> 头文件中定义,并且提供了类型安全和异常安全的保证。
然而,当需要最大化性能以及处理原始内存块时(如在自定义内存分配器中),memcpy 和 memmove 仍然是有用的工具。



