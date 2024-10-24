<cstdlib> 是 C++ 标准库中的一个头文件，包含了许多常用的 C 标准库函数
这些函数提供了各种实用功能，包括内存管理、程序退出、环境变量处理、数学运算等

主要函数
atof, atoi, atol, atoll
strtod, strtof, strtol, strtoll, strtoul, strtoull
rand, srand
calloc, malloc, realloc, free
abort
exit, quick_exit, _Exit
system
getenv, setenv, putenv, unsetenv
bsearch, qsort
abs, labs, llabs
div, ldiv, lldiv

1. atof, atoi, atol, atoll
这些函数用于将字符串转换为浮点数或整数

#include <iostream>
#include <cstdlib>

int main() {
    const char* floatStr = "3.14";
    const char* intStr = "42";
    const char* longStr = "1234567890";
    const char* longLongStr = "9223372036854775807";

    double d = atof(floatStr);
    int i = atoi(intStr);
    long l = atol(longStr);
    long long ll = atoll(longLongStr);

    cout << "atof: " << d << endl;
    cout << "atoi: " << i << endl;
    cout << "atol: " << l << endl;
    cout << "atoll: " << ll << endl;

    return 0;
}

2. strtod, strtof, strtol, strtoll, strtoul, strtoull
这些函数提供了更灵活的字符串转换功能, 允许指定进制和处理转换错误

#include <iostream>
#include <cstdlib>
#include <cerrno>

int main() {
    const char* str = "123.456abc";
    char* end;

    double d = strtod(str, &end);
    if (*end != '\0') {
        cout << "Remaining string: " << end << endl;
    }

    const char* intStr = "42";
    long l = strtol(intStr, nullptr, 10);

    cout << "strtod: " << d << endl;
    cout << "strtol: " << l << endl;

    return 0;
}

3. rand, srand
这些函数用于生成伪随机数
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // 使用当前时间作为种子

    for (int i = 0; i < 5; ++i) {
        cout << "Random number: " << rand() << endl;
    }

    return 0;
}

4. calloc, malloc, realloc, free
这些函数用于动态内存分配和释放

#include <iostream>
#include <cstdlib>

int main() {
    // 使用malloc分配内存
    int* p = static_cast<int*>(malloc(5 * sizeof(int)));
    if (p == nullptr) {
        cerr << "Memory allocation failed" << endl;
        return 1;
    }

    // 使用calloc分配内存并初始化为0
    int* q = static_cast<int*>(calloc(5, sizeof(int)));
    if (q == nullptr) {
        cerr << "Memory allocation failed" << endl;
        free(p);
        return 1;
    }

    // 使用realloc调整内存大小
    p = static_cast<int*>(realloc(p, 10 * sizeof(int)));
    if (p == nullptr) {
        cerr << "Memory reallocation failed" << endl;
        free(q);
        return 1;
    }

    // 释放内存
    free(p);
    free(q);

    return 0;
}

5. abort
abort 函数用于立即终止程序

#include <iostream>
#include <cstdlib>

int main() {
    cout << "This will be printed." << endl;
    abort();
    cout << "This will not be printed." << endl;

    return 0;
}

6. exit, quick_exit, _Exit
这些函数用于正常或异常终止程序

#include <iostream>
#include <cstdlib>

void cleanup() {
    cout << "Cleanup before exit." << endl;
}

int main() {
    atexit(cleanup);

    cout << "Exiting program..." << endl;
    exit(0); // 或者使用quick_exit(0)或者_Exit(0)

    return 0;
}

7. system
system 函数用于执行系统命令

#include <iostream>
#include <cstdlib>

int main() {
    system("ls -l"); // 在Windows上使用 system("dir")

    return 0;
}

8. getenv, setenv, putenv, unsetenv
这些函数用于获取和设置环境变量

#include <iostream>
#include <cstdlib>

int main() {
    const char* path = getenv("PATH");
    if (path != nullptr) {
        cout << "PATH: " << path << endl;
    }

    setenv("MY_VAR", "123", 1);
    cout << "MY_VAR: " << getenv("MY_VAR") << endl;

    unsetenv("MY_VAR");
    cout << "MY_VAR after unset: " << getenv("MY_VAR") << endl;

    return 0;
}

9. bsearch, qsort
这些函数用于二分查找和快速排序

#include <iostream>
#include <cstdlib>
#include <cstring>

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int arr[] = {4, 2, 3, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    // 快速排序
    qsort(arr, size, sizeof(int), compare);
    cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 二分查找
    int key = 3;
    int* item = static_cast<int*>(bsearch(&key, arr, size, sizeof(int), compare));
    if (item != nullptr) {
        cout << "Found key " << key << endl;
    } else {
        cout << "Key " << key << " not found" << endl;
    }

    return 0;
}

10. abs, labs, llabs
这些函数用于计算整数的绝对值

#include <iostream>
#include <cstdlib>

int main() {
    int i = -10;
    long l = -100000L;
    long long ll = -10000000000LL;

    cout << "abs: " << abs(i) << endl;
    cout << "labs: " << labs(l) << endl;
    cout << "llabs: " << llabs(ll) << endl;

    return 0;
}

11. div, ldiv, lldiv
这些函数用于整数除法，返回商和余数

#include <iostream>
#include <cstdlib>

int main() {
    int num = 10, denom = 3;
    div_t result = div(num, denom);
    cout << "div: " << result.quot << " R " << result.rem << endl;

    long lnum = 100000L, ldenom = 30000L;
    ldiv_t lresult = ldiv(lnum, ldenom);
    cout << "ldiv: " << lresult.quot << " R " << lresult.rem << endl;

    long long llnum = 10000000000LL, lldenom = 3000000000LL;
    lldiv_t llresult = lldiv(llnum, lldenom);
    cout << "lldiv: " << llresult.quot << " R " << llresult.rem << endl;

    return 0;
}
