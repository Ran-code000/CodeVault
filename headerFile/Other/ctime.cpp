<ctime>库是C++标准库的一部分, 提供了处理日期和时间的功能

1. time_t time(time_t* timer)

返回当前时间的秒数(从1970年1月1日00:00:00 UTC到当前时间的秒数)

#include <iostream>
#include <ctime>

int main() {
    time_t currentTime;
    time(&currentTime); // 获取当前时间
    cout << "Current time: " << currentTime << " seconds since the Epoch" << endl;
    return 0;
}

2. char* ctime(const time_t* timer)

将time_t类型的时间转换为本地时间并以字符串形式返回

#include <iostream>
#include <ctime>

int main() {
    time_t currentTime;
    time(&currentTime);
    char* localTimeStr = ctime(&currentTime); // 转换为本地时间字符串
    cout << "Local time: " << localTimeStr;
    return 0;
}

3. struct tm* localtime(const time_t* timer)

将time_t类型的时间转换为当地时间, 返回一个指向tm结构的指针

#include <iostream>
#include <ctime>

int main() {
    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime); // 转换为本地时间结构
    cout << "Year: " << 1900 + localTime->tm_year << endl;
    cout << "Month: " << 1 + localTime->tm_mon << endl;
    cout << "Day: " << localTime->tm_mday << endl;
    return 0;
}

4. struct tm* gmtime(const time_t* timer)

将time_t类型的时间转换为UTC时间, 并返回一个指向tm结构的指针

#include <iostream>
#include <ctime>

int main() {
    time_t currentTime;
    time(&currentTime);
    struct tm* utcTime = gmtime(&currentTime); // 转换为UTC时间结构
    cout << "Year: " << 1900 + utcTime->tm_year << endl;
    cout << "Month: " << 1 + utcTime->tm_mon << endl;
    cout << "Day: " << utcTime->tm_mday << endl;
    return 0;
}

5. time_t mktime(struct tm* timeptr)

将tm结构的本地时间转换为time_t格式

#include <iostream>
#include <ctime>

int main() {
    struct tm timeinfo = {};
    timeinfo.tm_year = 2024 - 1900; // 年份从1900开始
    timeinfo.tm_mon = 6 - 1; // 月份从0开始
    timeinfo.tm_mday = 22;
    time_t timeSinceEpoch = mktime(&timeinfo); // 转换为time_t格式
    cout << "Seconds since the Epoch: " << timeSinceEpoch << endl;
    return 0;
}
double difftime(time_t end, time_t beginning)

6. 计算两个time_t时间之间的差值(秒数)

#include <iostream>
#include <ctime>

int main() {
    time_t startTime, endTime;
    time(&startTime); // 记录开始时间
    // 模拟一些处理
    for (volatile int i = 0; i < 1000000; ++i);
    time(&endTime); // 记录结束时间
    double seconds = difftime(endTime, startTime); // 计算时间差
    cout << "Time taken: " << seconds << " seconds" << endl;
    return 0;
}
size_t strftime(char* str, size_t maxsize, const char* format, const struct tm* timeptr)

7. 根据格式化字符串format将tm结构格式化并存储到字符数组str中

#include <iostream>
#include <ctime>

int main() {
    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime); // 获取本地时间
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime); // 格式化时间
    cout << "Formatted time: " << buffer << endl;
    return 0;
}
clock_t clock(void)

8. 返回程序执行起始到当前所用的时间(CPU时间), 单位是时钟滴答数

#include <iostream>
#include <ctime>

int main() {
    clock_t start = clock(); // 记录开始时刻
    // 模拟一些处理
    for (volatile int i = 0; i < 1000000; ++i);
    clock_t end = clock(); // 记录结束时刻
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // 计算CPU时间
    cout << "CPU time used: " << cpu_time_used << " seconds" << endl;
    return 0;
}
以上是<ctime>库中一些常用函数的示例代码和解释
每个函数在处理日期和时间时都有其特定的用途, 根据具体需求选择合适的函数进行操作

