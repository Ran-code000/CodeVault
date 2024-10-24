<valarray> 是C++标准库中的一个头文件，提供了用于数值计算的类 valarray
valarray 类用于表示和操作数值数组，提供了高效的数学操作，并支持向量化

1. 创建 valarray
可以使用多种方式创建 valarray, 包括默认构造, 用特定值初始化, 用数组初始化等

#include <iostream>
#include <valarray>

int main() {
    // 默认构造
    valarray<int> val1;

    // 用特定值初始化
    valarray<int> val2(10);  // 大小为10，初始值为0
    valarray<int> val3(5, 10);  // 大小为10，初始值为5

    // 用数组初始化
    int arr[] = {1, 2, 3, 4, 5};
    valarray<int> val4(arr, 5);

    // 输出 val4 的值
    for (int i = 0; i < val4.size(); ++i) {
        cout << val4[i] << " ";
    }
    cout << endl;

    return 0;
}

2. 基本运算
valarray 支持基本的算术运算(加、减、乘、除等), 并且这些运算是逐元素进行的
#include <iostream>
#include <valarray>

int main() {
    valarray<int> val1 = {1, 2, 3, 4, 5};
    valarray<int> val2 = {6, 7, 8, 9, 10};

    // 加法
    valarray<int> sum = val1 + val2;

    // 输出 sum 的值
    for (int i = 0; i < sum.size(); ++i) {
        cout << sum[i] << " ";
    }
    cout << endl;

    return 0;
}

3. 元素访问和修改
可以使用 [] 运算符访问和修改 valarray 中的元素

#include <iostream>
#include <valarray>

int main() {
    valarray<int> val = {1, 2, 3, 4, 5};

    // 修改第一个元素
    val[0] = 10;

    // 输出 val 的值
    for (int i = 0; i < val.size(); ++i) {
        cout << val[i] << " ";
    }
    cout << endl;

    return 0;
}

4. 计算标准数学函数
valarray 支持许多标准数学函数(如 sin, cos, sqrt, log 等)

#include <iostream>
#include <valarray>
#include <cmath>

int main() {
    valarray<double> val = {0.0, 0.5, 1.0, 1.5, 2.0};

    // 计算每个元素的正弦值
    valarray<double> result = sin(val);

    // 输出 result 的值
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}

5. 切片操作
valarray 支持切片(slice)和选择(gslice)操作, 可以对数组的部分元素进行操作

#include <iostream>
#include <valarray>

int main() {
    valarray<int> val = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 创建一个切片（从索引2开始，长度为4，步长为2）
    slice_array<int> slice = val[slice(2, 4, 2)];

    // 将切片中的元素乘以10
    slice *= 10;

    // 输出 val 的值
    for (size_t i = 0; i < val.size(); ++i) cout << val[i] << " ";
    cout << endl;

    return 0;
}

6. 子数组操作
valarray 支持子数组(subarray)操作, 可以对连续的子数组进行操作

#include <iostream>
#include <valarray>

int main() {
    valarray<int> val = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 创建一个子数组（从索引2开始，长度为4）
    valarray<int> sub = val[slice(2, 4, 1)];

    // 将子数组中的元素加5
    sub += 5;

    // 输出 val 的值
    for (size_t i = 0; i < val.size(); ++i) {
        cout << val[i] << " ";
    }
    cout << endl;

    return 0;
}

7. 其他有用的操作
valarray 还支持许多其他有用的操作, 如求和, 最小值, 最大值等

#include <iostream>
#include <valarray>
#include <algorithm>  // for min and max

int main() {
    valarray<int> val = {1, 2, 3, 4, 5};

    // 求和
    int sum = val.sum();
    cout << "Sum: " << sum << endl;

    // 最小值
    int min = val.min();
    cout << "Min: " << min << endl;

    // 最大值
    int max = val.max();
    cout << "Max: " << max << endl;

    // 平均值
    double mean = val.sum() / static_cast<double>(val.size());
    cout << "Mean: " << mean << endl;

    return 0;
}

8. 元素按条件筛选
可以使用掩码数组(mask array)选择满足特定条件的元素

#include <iostream>
#include <valarray>

int main() {
    valarray<int> val = {1, 2, 3, 4, 5};

    // 创建一个掩码数组，选择大于3的元素
    valarray<bool> mask = val > 3;

    // 输出符合条件的元素
    for (size_t i = 0; i < val.size(); ++i) {
        if (mask[i]) {
            cout << val[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
